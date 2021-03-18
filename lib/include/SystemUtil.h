#ifndef SYSTEMUTIL_H
#define SYSTEMUTIL_H 
#include <stdint.h>

uint32_t  getControllerStatus();
uint32_t  getThreadQueueManager();
uint32_t  getTimerTicks();

#endif