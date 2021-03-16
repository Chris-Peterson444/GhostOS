#ifndef THREADS_H
#define THREADS_H

#define MAX_THREADS 10

typedef uint32_t TCPUInterruptState, *TCPUInterruptSateRef;
typedef uint32_t *TCPUStackRef;
typedef uint32_t (*TCPUContextEntry)(void *param);

typedef struct ThreadContext {
	TCPUStackRef stackPointer;
	uint32_t threadID;
	TCPUContextEntry entryFunc;
	uint32_t mepcVal;
} ThreadContext;

typedef struct ThreadQueue {
	ThreadContext queue[MAX_THREADS];
	uint32_t currentThread;
	uint32_t nextFree;
	uint32_t fill;
} ThreadQueue;




//Assembly defined
TCPUStackRef CPUHALContextInitialize(TCPUStackRef stacktop, TCPUContextEntry entry, void *param);
// void CPUHALContextSwitch(TCPUStackRef *storecurrent, TCPUStackRef restore);
void CPUHALContextSwitch(TCPUStackRef restore);

//C defined
void threadInit();
uint32_t CPUHALAddThread(ThreadQueue *queue,TCPUStackRef stacktop, TCPUContextEntry entry);
uint32_t CPUHALRemoveThread(ThreadQueue *queue, uint32_t threadID);
void CPUHALSwitchThread(ThreadQueue *queue);

#endif