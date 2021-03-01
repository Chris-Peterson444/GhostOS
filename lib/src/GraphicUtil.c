
#include "GraphicUtil.h"
#include "SystemCallCodes.h"

SystemCall(uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5);

uint32_t setImage(uint32_t image, uint32_t x, uint32_t y, uint32_t z, uint32_t palette){

	return SystemCall(SETIMAGE, image, x, y, z, palette);

}

uint32_t setPalette(uint32_t background, uint32_t* buff){

	return SystemCall(FILLPALETTE, buff, -1, -1, -1, -1);
}

uint32_t moveImage(uint32_t image, uint32_t x, uint32_t y, uint32_t z){
	return SystemCall(MOVEIMAGE, image, x, y, z, -1);
}

uint32_t setImagePalette(uint32_t image, uint32_t palette){
	return SystemCall(SETIMAGEPALETTE, image, palette, -1, -1, -1);
}

uint32_t renderSprite(){
	return 0;
}

uint32_t graphicsMode(uint32_t mode){
	return SystemCall(GRAPHICMODESET, mode, -1, -1, -1, -1);
}

uint32_t printText(char * buff, uint32_t size){
	return SystemCall(PRINTTEXT, buff, size, -1, -1, -1);
}

uint32_t setRefreshRate(uint32_t rate){
	return SystemCall(REFRESHRATE, rate, -1, -1, -1, -1);
}

uint32_t imageFill(uint32_t background, uint8_t* buff, uint32_t size){
	return SystemCall(FILLIMAGE, background, buff, size, -1, -1);
}