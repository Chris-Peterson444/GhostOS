#include <stdint.h>
#include "Syscalls.h"
#include "ChipsetRegisters.h"
#include "VideoControllerUtility.h"


/*
	Returns the controller status as a (byte-sized) bitmap
*/
uint32_t  _getControllerStatus(){
	return  CONTROLLER_STATUS & (uint32_t) 0xFF;
	
}


uint32_t _setImage(uint32_t image, uint32_t x, uint32_t y, uint32_t z, uint32_t palette){
	return _imageSet(image, x,  y,  z, palette);
}

uint32_t _moveImage(uint32_t image, uint32_t x, uint32_t y, uint32_t z){
	return _imageMove(image, x, y, z);
}


uint32_t _renderSprite(){
	return 0;
}

/*
	Set the graphics mode
*/

uint32_t _graphicsMode(uint32_t mode){
	if(mode==1){
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

/*
	Print text to the scrren
*/

uint32_t _printText(char *buff, uint32_t size){
	return _fillText(buff, size);
}

uint32_t _setImagePalette(uint32_t image, uint32_t palette){
	_imagePaletteSet( image, palette);
}


uint32_t _setPalette(uint32_t background, uint32_t* buff){

	return _fillPalette( background, buff);

}

uint32_t _imageFill(uint32_t background, uint8_t* buff, uint32_t size){
	return _fillImage( background, buff, size);
}


