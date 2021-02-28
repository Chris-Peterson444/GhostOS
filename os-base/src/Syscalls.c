#include <stdint.h>
#include "Syscalls.h"
#include "ChipsetRegisters.h"
#include "VideoControllerUtility.h"


/*
	Returns the controller status as a (byte-sized) bitmap
*/
uint8_t  _getControllerStatus(){
	uint8_t status = CONTROLLER_STATUS & (uint32_t) 0xFF;
	return status;
}


uint32_t _setBackground(){
	return 0;
}

uint32_t _setPalette(){
	return 0;
}

uint32_t _renderSprite(){
	return 0;
}

/*
	Set the graphics mode
*/

uint32_t _graphicsMode(uint32_t mode){
	if(mode){
		graphics_graphic_mode();
	}
	else{
		graphics_text_mode();
	}
	return 1;
}


/* 
	Set the screen refresh rate
	Returns the set rate
*/
uint32_t _setRefreshRate(uint32_t rate){
	return graphics_refresh_rate(rate);

}

uint32_t _printText(){
	return 0;
}

uint32_t _sleep(uint32_t milliseconds){
	return 0;
}
