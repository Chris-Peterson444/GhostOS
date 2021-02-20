#ifndef VIDEOCONTROLLERUTILITY_DEF_H
#define VIDEOCONTROLLERUTILITY_DEF_H
#include "ChipsetRegisters.h"
#include "VideoControllerMap.h"


__attribute__((always_inline)) inline void graphics_mode(int mode){
	if(mode==0){
		GRAPHICS_MODE_CONTROL = GRAPHICS_MODE_CONTROL | (uint32_t) 0x1;
	}
	else{
		GRAPHICS_MODE_CONTROL = GRAPHICS_MODE_CONTROL & (uint32_t) 0x0;
	}
}

__attribute__((always_inline)) inline void graphics_text_mode(void){
    GRAPHICS_MODE_CONTROL = GRAPHICS_MODE_CONTROL & (uint32_t) 0x0;
}

__attribute__((always_inline)) inline void graphics_graphic_mode(void){
    GRAPHICS_MODE_CONTROL = GRAPHICS_MODE_CONTROL | (uint32_t) 0x1;
}

__attribute__((always_inline)) inline void graphics_refresh_rate(uint32_t rate){
	if (rate > 127 || rate < 0){
		rate = 0;
	}
	rate = rate << 1;
	// uint32_t mask = GRAPHICS_MODE_CONTROL & 0xFFFFFF01
 //    uint32_t mask = 0x64 | 0x1;
    GRAPHICS_MODE_CONTROL = GRAPHICS_MODE_CONTROL & rate;
}


#endif