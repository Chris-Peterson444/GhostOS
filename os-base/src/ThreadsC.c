#include <stdint.h>
#include <stdio.h>
#include "Threads.h"
#include "StatusRegisterUtility.h"


// volatile ThreadQueue osThreadQueue = {.currentThread = 0, .nextFree = 1};
// register char *stack_ptr asm ("sp");

//This is only run by the main thread of the system
void _threadInit(ThreadQueueManager *manager){

	//Set the main stack pointer
	register char *stack_ptr asm ("sp");
	manager->mainStackPointer = stack_ptr;

	//Set the main thread info
    manager->osThreadQueue.fill = 1;
    manager->osThreadQueue.currentThread = 0;
    manager->osThreadQueue.nextFree = 1;
    manager->osThreadQueue.queue[0].threadID = 0;   // Give our first thread an ID
    manager->osThreadQueue.queue[0].entryFunc = -1; // Give our first thread a special entry value

}

uint32_t CPUHALQueueThread(ThreadQueue *queue,TCPUStackRef stacktop, TCPUContextEntry entry){

	//If the queue is full, can't add more
	int free = queue->nextFree;
	if (free == -1){
		return -1;
	}
		
	ThreadContext *context = &(queue->queue[queue->nextFree]);
	context->stackPointer = stacktop;
	context->threadID = free;
	context->entryFunc = entry;
	context->mepcVal = (uint32_t) *entry;
	queue->fill++;

	if (free + 1 < MAX_THREADS){
		free = queue->nextFree++;
	}
	return free;
}

uint32_t CPUHALAddThread(volatile ThreadQueueManager* manager, TCPUStackRef stacktop, TCPUContextEntry entry, int type){

	uint32_t rv;
	TCPUInterruptState PreviousState = CPUHALSuspendInterrupts();
	switch (type){
		case OS_THREAD:  rv = CPUHALQueueThread(&(manager->osThreadQueue), stacktop, entry);
						 break;
		case APP_THREAD: rv = CPUHALQueueThread(&(manager->appThreadQueue), stacktop, entry);
						 break;
	}
	CPUHALResumeInterrupts(PreviousState);
	return rv;
}

uint32_t CPUHALRemoveThread(ThreadQueue *queue, uint32_t threadID){
	return 0;
}

void CPUHALSwitchThread(ThreadQueue *queue){

	// ThreadQueue *queue = &(manager->osThreadQueue);
	int id = queue->currentThread;
	int newID;

	// Always going to go left to right in queue
	//Check if at the end of the queue
	if ( (id == MAX_THREADS - 1) || (id == queue->fill - 1) ){
		newID = 0;
	}
	else{
		newID = id + 1;
	}
	queue->currentThread = newID;


	//Get the current threads value in the MEPC and store it for the thread
	uint32_t currMepc = csr_mepc_read();
	queue->queue[id].mepcVal = currMepc;

	//Get the pre-interrupt stackpointer and save it
	uint32_t tp = thread_pointer_read();
	queue->queue[id].stackPointer = (uint32_t *) tp;

	//Change the MEPC value to the previous threads
	csr_mepc_write(queue->queue[newID].mepcVal);

	//Reset the stack and jump out
	CPUHALContextSwitch(queue->queue[newID].stackPointer);
	//Nothing below this line is executed!!

}