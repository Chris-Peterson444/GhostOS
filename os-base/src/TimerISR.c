/*
* @Author: Chris Peterson
* @Date:   2021-02-24 16:37:53
* @Last Modified by:   Chris Peterson
* @Last Modified time: 2021-02-24 16:45:45
*/

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