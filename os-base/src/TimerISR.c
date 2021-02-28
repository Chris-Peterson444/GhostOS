#include "isr/TimerISR.h"

#include <stdint.h>
#include "ChipsetRegisters.h"

extern volatile int global;
extern volatile uint32_t controller_status;
extern void timer_callback(void);

void timer_ISR(void){

    uint64_t NewCompare = (((uint64_t)MTIMECMP_HIGH)<<32) | MTIMECMP_LOW;
    NewCompare += 10;
    MTIMECMP_HIGH = NewCompare>>32;
    MTIMECMP_LOW = NewCompare;
	timer_callback();
	global++;
	controller_status = CONTROLLER_STATUS;
 

}