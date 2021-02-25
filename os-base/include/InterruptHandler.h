#ifndef INTERRUPTHANDLER_H
#define INTERRUPTHANDLER_H

#include <stdint.h>
#include "isr/CmdISR.h"
#include "isr/TimerISR.h"

uint32_t c_syscall(uint32_t param);

void c_interrupt_handler(void);


#endif


