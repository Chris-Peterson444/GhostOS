#ifndef THREADS_H
#define THREADS_H
#include <stdint.h>

#define MAX_THREADS 10
#define OS_THREAD 1
#define APP_THREAD 2

#define OS_QUEUE 1
#define APP_QUEUE 2

#define true 1
#define false 0

typedef uint32_t TCPUInterruptState, *TCPUInterruptSateRef;
typedef uint32_t *TCPUStackRef;
typedef uint32_t (*TCPUContextEntry)(void *param);

typedef struct ThreadContext {
	TCPUStackRef stackPointer;
	uint32_t threadID;
	TCPUContextEntry entryFunc;
	uint32_t mepcVal;
	int ready;
} ThreadContext;

typedef struct ThreadQueue {
	ThreadContext queue[MAX_THREADS];
	uint32_t currentThread;
	uint32_t nextFree;
	uint32_t fill;
	uint32_t nextThread;
} ThreadQueue;

typedef struct ThreadQueueManager {
	ThreadQueue osThreadQueue;
	ThreadQueue appThreadQueue;
	char *mainStackPointer;
	int currQueue;
} ThreadQueueManager;


//Assembly defined
TCPUStackRef CPUHALContextInitialize(TCPUStackRef stacktop, TCPUContextEntry entry, void *param);
void CPUHALContextSwitch(TCPUStackRef restore);

//C defined

// Init threads for the OS
void _threadInit(ThreadQueueManager *manager);
uint32_t CPUHALQueueThread(ThreadQueue *queue, TCPUStackRef stacktop, TCPUContextEntry entry);
uint32_t CPUHALAddThread(volatile ThreadQueueManager* manager, TCPUStackRef stacktop, TCPUContextEntry entry, int type);
uint32_t CPUHALRemoveThread(ThreadQueue *queue, uint32_t threadID);
void CPUHALThreadSwitch(volatile ThreadQueueManager* manager);



#endif