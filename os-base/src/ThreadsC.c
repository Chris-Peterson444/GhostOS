#include <stdint.h>
#include <stdio.h>
#include "Threads.h"
#include "StatusRegisterUtility.h"

void switchThreads(ThreadContext *oldContext, ThreadContext* newContext);
void softwareSwitch(ThreadContext *oldContext, ThreadContext* newContext);

//Want a pointer to the main OS thread manager
ThreadQueueManager *mainManager;


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
    manager->osThreadQueue.queue[0].ready = READY;   //Make our first thread ready
    manager->osThreadQueue.queue[0].wasSuspended = false;

    //Get a local reference for syscalls
    mainManager = manager;

}

ThreadContext* CPUHALQueueThread(volatile ThreadQueue *queue,TCPUStackRef stacktop, TCPUContextEntry entry){

	//If the queue is full, can't add more
	int free = queue->nextFree;
	if (free > MAX_THREADS -1){
		return NULL;
	}
	queue->nextFree += 1;
	ThreadContext *context = &(queue->queue[queue->nextFree]);
	context->stackPointer = stacktop;
	context->threadID = free;
	context->entryFunc = entry;
	context->mepcVal = (uint32_t) *entry;
	context->ready = READY;
	context->wasSuspended = false;
	queue->fill++;

	printf("adding thread %d\n",free);
	fflush(stdout);

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

//Called from inside the OS 
void _CPUHALThreadSuspend(ThreadContext* context){
	int ready = context->ready;
	// TCPUInterruptState PreviousState = CPUHALSuspendInterrupts();

	//I could do something like give up the thread early, but that's for the future
	// CPUHALThreadSwitch(mainManager, NON_INTERRUPT);

	while(!ready){
		ready = context->ready;
	}

	// CPUHALThreadSwitch(mainManager);
	// CPUHALResumeInterrupts(PreviousState);

}

//Need a separate version of this for the application
void CPUHALThreadStatus(ThreadContext* context, int ready){
	context->ready = ready;

	ThreadContext* thisContext = (ThreadContext* ) CPUHALGetSelfContext();
	// Check if we're setting ourself to wait
	if( (thisContext == context) && ready == WAIT){
		_CPUHALThreadSuspend(context);
	}

}

ThreadContext* CPUHALGetSelfContext(){
	ThreadContext *context = (ThreadContext *) thread_pointer_read();
	return context;
}

void CPUHALThreadSwitch(volatile ThreadQueueManager* manager, int caller){

	ThreadQueue *workingQueue;
	ThreadQueue *otherQueue;
	int oldQueue = manager->currQueue;
	switch(oldQueue){
		case OS_QUEUE: 		workingQueue = &(manager->osThreadQueue);
					   		otherQueue = &(manager->appThreadQueue);
					   		break;
		case APP_QUEUE: 	workingQueue = &(manager->appThreadQueue);
							otherQueue = &(manager->osThreadQueue);
							break;
		default:
			printf("Invalid Thread Queue\n");
			fflush(stdout);
			return;
	}

	int newQueue;
	ThreadContext *oldContext;
	ThreadContext *newContext;
	// ThreadQueue *tempQueue;
	int oldID = workingQueue->currentThread;
	int newID;

	oldContext = &(workingQueue->queue[oldID]);

	int found = false;


	//Check if at the end of the queue. 
	if (oldID == (workingQueue->fill - 1)){
		// printf("in here\n");
		// fflush(stdout);
		//Check if there's anything to do in the other queue
		if( otherQueue->fill == 0){
			// don't switch queues, but switch threads
			newID = 0;
			while(!found){
				if(workingQueue->queue[newID].ready == READY){
					found = true;
				}
				else{
					newID++;
					if(newID == workingQueue->fill - 1){
						// if we got here then we cycled and all threads are disabled. whoops.
						//Re-enabling main OS thread 
						newID = 0;
						workingQueue = &(manager->osThreadQueue);
						//Optionally print if problem
						printf("Disabled all threads. Renabling thread 0\r");
						fflush(stdout);
					}
				}
			}
			workingQueue->nextThread = newID + 1;
			if(newID + 1 >= workingQueue->fill){
				workingQueue->nextThread = 0;
			}
			workingQueue->currentThread = newID;
			newContext = &(workingQueue->queue[newID]);

		if(workingQueue == &(manager->osThreadQueue)){
			newQueue = OS_QUEUE;
		}
		else{
			newQueue = APP_QUEUE;
		}

		}
		else{
			//switch
			// printf("in here\n");
			// fflush(stdout);
			//do some bookkeeping on the old queue before switching
			workingQueue->nextThread = 0;
			workingQueue->currentThread = -1;

			//Work on the new queue
			newID = otherQueue->nextThread;
			int cyle = newID;
			while(!found){
				
				if(otherQueue->queue[newID].ready == READY){
					found = true;
				}
				else{
					newID++;
					if(newID == otherQueue->fill - 1){
						// No ready threads found yet, checking the other end
						newID = 0;
					}
					else if (newID == cyle){
						//if we get here then we cycled and found no ready threads. lets go back to the other queue
						newID = workingQueue->nextThread;
						cyle = workingQueue->fill;
						otherQueue = workingQueue;
					}
				}

			}

			otherQueue->currentThread = newID;
			otherQueue->nextThread = newID + 1;
			// if(newID + 1 > otherQueue-> fill - 1){

			// }
			if(otherQueue->nextThread >= otherQueue->fill - 1){
				otherQueue->nextThread = 0;
			}
			newContext = &(otherQueue->queue[newID]);
		}

		if(otherQueue == &(manager->osThreadQueue)){
			newQueue = OS_QUEUE;
		}
		else{
			newQueue = APP_QUEUE;
		}
	}
	else{
		//There's more in the queue
		newID = workingQueue->nextThread;
		ThreadQueue *tempQueue = workingQueue;
		// printf("working queue @%08X\n",workingQueue);
		// printf("temp queue    @%08X\n",tempQueue);
		// fflush(stdout);
		while(!found){
			if(tempQueue->queue[newID].ready == READY){
				found = true;
			}
			else{
				newID++;
				if(newID == tempQueue->fill - 1){
					//Reach end of queue without finding anything

					//Try other queue first, but only if it's not empty
					if(otherQueue->fill > 0){
						if(tempQueue == workingQueue){
							newID = otherQueue->nextThread;
							tempQueue = otherQueue;
						}
					}
					//Lets try the beginning of our original queue
					else{
						newID = 0;
						tempQueue = workingQueue;
					}
				}
			}
		}

		tempQueue->currentThread  = newID;
		tempQueue->nextThread = newID + 1;
		if(tempQueue->nextThread >= tempQueue->fill){
			tempQueue->nextThread = 0;
		}
		newContext = &(tempQueue->queue[newID]);

		if(tempQueue == &(manager->osThreadQueue)){
			newQueue = OS_QUEUE;
		}
		else{
			newQueue = APP_QUEUE;
		}
	}


	manager->currQueue = newQueue;

	if(caller == INTERRUPT){
		switchThreads(oldContext, newContext);
	}
	else{
		softwareSwitch(oldContext, newContext);
	}

}

//Only come in from interrupt service routine
void switchThreads(ThreadContext *oldContext, ThreadContext* newContext){

	// printf("entered interrupt switch\n");
	// fflush(stdout);
	// printf("switching\n");
	// fflush(stdout);

	// printf("New ThreadID: %d   NewMEPC: %08X\n",newContext->threadID,newContext->mepcVal);
	// fflush(stdout);

	//Get the current threads value in the MEPC and store it for the thread
	uint32_t currMepc = csr_mepc_read();
	oldContext->mepcVal = currMepc;

	//Get the pre-interrupt stackpointer and save it
	uint32_t tp = thread_pointer_read();
	oldContext->stackPointer = (uint32_t *) tp;

	// //Change the MEPC value to the previous threads
	// csr_mepc_write(newContext->mepcVal);

	// 	printf("oldContext ID,RS,SS: %d,%d,%d  newContext ID,RS,SS: %d,%d,%d\n",oldContext->threadID,oldContext->ready, oldContext->wasSuspended, newContext->threadID, newContext->ready, newContext->wasSuspended);
	// fflush(stdout);
	//Special return for suspended processes
	if(newContext->wasSuspended == true){
		printf("There was a suspended context. It was thread %d\n", newContext->threadID);
		fflush(stdout);
		//Set flag
		newContext->wasSuspended = false;
		CPUHALNonInterruptContextSwitchIntToSoft(newContext->stackPointer, newContext);
	}
	else{
		// printf("only here\n");
		// fflush(stdout);
		//Reset the stack and jump out

		//Change the MEPC value to the previous threads
		csr_mepc_write(newContext->mepcVal);

		CPUHALContextSwitch(newContext->stackPointer, newContext);
	}

}

//Come in from software
void softwareSwitch(ThreadContext *oldContext, ThreadContext* newContext){
	printf("entered software switch\n");
	fflush(stdout);
	//Get the current threads return value and store it as the mepc for the thread
	uint32_t returnAddress = reg_ra_read();
	oldContext->mepcVal = returnAddress;
	oldContext->wasSuspended = true;
	printf("second\n");
	fflush(stdout);
	// //Get the current stackpointer and save it
	// uint32_t sp = reg_sp_read();
	// oldContext->stackPointer = (uint32_t *) sp;
	// printf("oldContext ID: %d  newContext ID: %d\n",oldContext->threadID, newContext->threadID);
	// fflush(stdout);
	if(newContext->wasSuspended == true){
		//Set flag
		newContext->wasSuspended = false;
		CPUHALNonInterruptContextSwitchSoftToSoft(&(oldContext->stackPointer),newContext->stackPointer, newContext);
	}
	else{
		//Change the MEPC value to the previous threads
		csr_mepc_write(newContext->mepcVal);
		//Save the Old stack, reset the new one and jump out
		CPUHALNonInterruptContextSwitchSoftToInt(&(oldContext->stackPointer),newContext->stackPointer, newContext);
	}

	
}