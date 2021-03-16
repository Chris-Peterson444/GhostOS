#include <stdint.h>
#include <stdio.h>
#include "Threads.h"
#include "StatusRegisterUtility.h"


uint32_t CPUHALAddThread(ThreadQueue *queue,TCPUStackRef stacktop, TCPUContextEntry entry){

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

uint32_t CPUHALRemoveThread(ThreadQueue *queue, uint32_t threadID){
	return 0;
}

void CPUHALSwitchThread(ThreadQueue *queue){

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

 	//Useless return for compiler
	return 0;
}