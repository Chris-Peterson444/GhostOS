#include "SystemUtil.h"
#include "SystemCallCodes.h"

#include <stdint.h>

uint32_t SystemCall(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5);

uint32_t  getControllerStatus(){
	return SystemCall(CONTROLLERSTATUS, -1, -1, -1, -1, -1);
}

uint32_t getThreadQueueManager(){
	return SystemCall(THREADMANAGER, -1, -1, -1, -1, -1);
}

uint32_t  getTimerTicks(){
	return SystemCall(TIMERTICKS, -1, -1, -1, -1, -1);
}