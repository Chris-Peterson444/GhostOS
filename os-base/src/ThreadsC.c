#include <stdint.h>
#include <stdio.h>
#include "Threads.h"
#include "StatusRegisterUtility.h"

void switchThreads(ThreadContext *oldContext, ThreadContext* newContext);

//This is only run by the main thread of the system
void _threadInit(ThreadQueueManager *manager){

	//Set the main stack pointer
	register char *stack_ptr asm ("sp");
	manager->mainStackPointer = stack_ptr;
	manager->currQueue = OS_QUEUE;

	//Set the main thread info
    manager->osThreadQueue.fill = 1;
    manager->osThreadQueue.currentThread = 0;
     manager->osThreadQueue.nextThread = 1;
    manager->osThreadQueue.nextFree = 1;
    manager->osThreadQueue.queue[0].threadID = 0;   // Give our first thread an ID
    manager->osThreadQueue.queue[0].entryFunc = (TCPUContextEntry) -1; // Give our first thread a special entry value
    manager->osThreadQueue.queue[0].ready = true;   //Make our first thread ready

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

void CPUHALThreadSwitch(volatile ThreadQueueManager* manager){

	ThreadQueue *workingQueue;
	ThreadQueue *otherQueue;

	switch(manager->currQueue){
		case OS_QUEUE: 		workingQueue = &(manager->osThreadQueue);
					   		otherQueue = &(manager->appThreadQueue);
					   		break;
		case APP_THREAD:	workingQueue = &(manager->appThreadQueue);
							otherQueue = &(manager->osThreadQueue);
							break;
		default:
			printf("Invalid Thread Queue\n");
			fflush(stdout);
			return;
	}

	ThreadContext *oldContext;
	ThreadContext *newContext;
	int oldID = workingQueue->currentThread;
	int newID;

	oldContext = &(workingQueue->queue[oldID]);

	//Check if at the end of the queue. 
	if (oldID == (workingQueue->fill - 1)){

		//Check if there's anything to do in the other queue
		if( otherQueue->fill == 0){
			// don't switch queues, but switch threads
			workingQueue->nextThread = 1;
			workingQueue->currentThread = 0;
			newContext = &(workingQueue->queue[0]);
		}
		else{
			//switch
			//do some bookkeeping on the old queue before switching
			workingQueue->nextThread = 0;
			workingQueue->currentThread = -1;

			//Work on the new queue
			otherQueue->currentThread = otherQueue->nextThread;
			otherQueue->nextThread++;
			if(otherQueue->nextThread == otherQueue->fill){
				otherQueue->nextThread = 0;
			}
			newContext = &(otherQueue->queue[otherQueue->currentThread]);
		}
	}
	else{
		//There's more in the queue
		workingQueue->currentThread  = workingQueue->nextThread;
		workingQueue->nextThread++;
		if(workingQueue->nextThread == workingQueue->fill){
			workingQueue->nextThread = 0;
		}
		newContext = &(workingQueue->queue[workingQueue->currentThread]);
	}
	switchThreads(oldContext, newContext);

}

void switchThreads(ThreadContext *oldContext, ThreadContext* newContext){

	//Get the current threads value in the MEPC and store it for the thread
	uint32_t currMepc = csr_mepc_read();
	oldContext->mepcVal = currMepc;

	//Get the pre-interrupt stackpointer and save it
	uint32_t tp = thread_pointer_read();
	oldContext->stackPointer = (uint32_t *) tp;

	//Change the MEPC value to the previous threads
	csr_mepc_write(newContext->mepcVal);

	//Reset the stack and jump out
	CPUHALContextSwitch(newContext->stackPointer);
	//Nothing below this line is executed!!
}