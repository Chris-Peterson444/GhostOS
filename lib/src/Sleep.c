#include <stdint.h>
#include <float.h>
#include "Sleep.h"
#include "Timer.h"
#include "ChipsetRegisters.h"
#include "SystemUtil.h"

uint32_t TimerTicks;
uint32_t period;
uint32_t timer_res = TIMER_TICKS_RES;
long long goalTime;

/*

TimerTicks is incremented for every TIMER_TICKS_RES machineticks.
Each machine tick has a period of MACHINE_CLOCK_REG in microseconds.

*/

uint32_t sleep(uint32_t miliseconds){
	period = (uint32_t) MACHINE_CLOCK_REG;          //Period in microseconds
	goalTime = miliseconds * 1000;                  //Goal   in microseconds
	uint32_t lastTick = TimerTicks;
	uint32_t ticksElapsed = 0;
	uint32_t compare = 0;

	while(1){
		TimerTicks = getTimerTicks();
		if(goalTime <= compare){
			break;
		}
		if(lastTick != TimerTicks){
			ticksElapsed += TimerTicks - lastTick;
			compare = ticksElapsed * timer_res * period;
		}
		lastTick = TimerTicks;
	}

	return compare/1000;
}