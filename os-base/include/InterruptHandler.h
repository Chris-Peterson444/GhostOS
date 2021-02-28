#ifndef INTERRUPTHANDLER_H
#define INTERRUPTHANDLER_H

#include <stdint.h>
#include "isr/CmdISR.h"
#include "isr/TimerISR.h"

uint32_t c_syscall(uint32_t code, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5);

void c_interrupt_handler(void);


#endif


