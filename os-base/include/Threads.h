#ifndef THREADS_H
#define THREADS_H

typedef uint32_t TCPUInterruptState, *TCPUInterruptSateRef;
typedef uint32_t *TCPUStackRef;
typedef uint32_t (*TCPUContextEntry)(void *param);

TCPUStackRef CPUHALContextInitialize(TCPUStackRef stacktop, TCPUContextEntry entry, void *param);
void CPUHALContextSwitch(TCPUStackRef *storecurrent, TCPUStackRef restore);

#endif