#ifndef VIDEOCONTROLLERUTILITY_H
#define VIDEOCONTROLLERUTILITY_H
#include <stdint.h>
#include "VideoControllerUtility_def.h"

/* Set graphics mode.
Modes:
	Text - 0
	Graphics - 1
*/
__attribute__((always_inline)) inline void graphics_mode(int mode);

//Sugar for graphics_mode(0)
__attribute__((always_inline)) inline void graphics_text_mode(void);

//sugar for graphics_mode(1)
__attribute__((always_inline)) inline void graphics_graphic_mode(void);

/* Set the refresh rate for the video controller. 
 Refresh rate is default set to 10 ticks per clock cycle (rate=0)
 Valid values of rate are [1, 127]
*/
__attribute__((always_inline)) inline uint32_t graphics_refresh_rate(uint32_t rate);

#endif