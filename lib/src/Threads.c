#include <stdint.h>
#include "ThreadInterface.h"
#include "StatusRegisterUtility.h"


ThreadQueueManager *mainManager;

//This is only run by the application thread
void appThreadinit(ThreadQueueManager *manager){
	mainManager = manager;
	register char *stack_ptr asm ("sp");
	manager->appStackPointer = stack_ptr;
}

ThreadContext* CPUHALQueueThread(volatile ThreadQueue *queue,TCPUStackRef stacktop, TCPUContextEntry entry){

	//If the queue is full, can't add more
	int free = queue->nextFree;
	if (free > MAX_THREADS -1){
		return 0;
	}
	queue->nextFree += 1;

	ThreadContext *context = &(queue->queue[free]);
	context->stackPointer = stacktop;
	context->threadID = free;
	context->entryFunc = entry;
	context->mepcVal = (uint32_t) *entry;
	context->ready = (int) READY;
	context->wasSuspended = false;
	queue->fill++;

	if (free + 1 < MAX_THREADS){
		free = queue->nextFree++;
	}
	return context;
}

ThreadContext* CPUHALAddThread(volatile ThreadQueueManager* manager, TCPUStackRef stacktop, TCPUContextEntry entry, int type){

	ThreadContext*  rv;
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

TCPUStackRef InitializeThreadStack(TCPUStackRef stacktop, TCPUContextEntry entry, void *param){
	return CPUHALContextInitialize( stacktop, entry, param);
}

void _CPUHALThreadSuspend(ThreadContext* context){
	int ready = context->ready;

	//I could do something like give up the thread early, but that's for the future
	// CPUHALThreadSwitch(mainManager, NON_INTERRUPT);

	while(!ready){
		ready = context->ready;
	}

}

//Need a separate version of this for the application
void CPUHALThreadStatus(ThreadContext* context, int ready){
	context->ready = ready;

	ThreadContext* thisContext = (ThreadContext* ) CPUHALGetSelfContext();
	// Check if we're setting ourself to wait
	if( (thisContext == context) && (ready == WAIT)){
		_CPUHALThreadSuspend(context);
	}

}

ThreadContext* CPUHALGetSelfContext(){
	ThreadContext *context = (ThreadContext *) thread_pointer_read();
	return context;
}