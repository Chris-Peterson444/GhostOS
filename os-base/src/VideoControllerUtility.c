#include "VideoControllerUtility.h"
#include "VideoControllerMap.h"

uint32_t _fillText(char *buff, uint32_t size){
	// If not in text mode, should fail
	if( (GRAPHICS_MODE_CONTROL & (uint32_t) 0x1) == 0x1 ){
		return -1;
	}

	//Else fill video memory up to size of memory
	// To-do: Do this with DMA later

	// Check if size > screen size
	uint32_t length = 0;
	if (size > SCREEN_BUFF_SIZE){
		length = SCREEN_BUFF_SIZE;
	}
	else{
		length = size;
	}

	volatile char * fill = (char *) &TEXT_DATA;
	//Fill screen with text
	for(int i = 0; i < length; i++){
		fill[i] = buff[i];
	}

	return 1;
}

uint32_t _fillImage(uint32_t background, uint8_t* buff, uint32_t size){

	//fill video memory up to size of memory
	// To-do: Do this with DMA later

	// Check if size > screen size
	uint32_t length = 0;
	if (size > IMAGE_BUFF_SIZE){
		length = IMAGE_BUFF_SIZE;
	}
	else{
		length = size;
	}

	uint8_t * img = (uint8_t *)  &BACKGROUND_DATA_IMG_0 + (background * 0x24000);

	for(uint32_t i = 0; i < length; i++){
		img[i] = buff[i];
	}

	return 1;

}

uint32_t _fillPalette(uint32_t background, uint32_t* buff){

	//fill video memory up to size of memory
	// To-do: Do this with DMA later


	uint32_t * palette = (uint32_t *)  &BACKGROUND_PALETTE_0 + (background * 0x400);

	for(uint32_t i = 0; i < PALETTE_SIZE; i++){
		palette[i] = buff[i];
	}

	return 1;

}

uint32_t _imageMove(uint32_t image, uint32_t x, uint32_t y, uint32_t z){

	uint32_t _palette = *(&BACKGROUND_CTRL_0 + (image * 0x4)) & 0b11;

	return _imageSet(image,x,y,z,_palette);

}

uint32_t _imageSet(uint32_t image, uint32_t x, uint32_t y, uint32_t z, uint32_t pallete){
	uint32_t * img_ptr = (uint32_t *) &BACKGROUND_CTRL_0 + (image * 0x4);
	uint32_t old_val = *img_ptr;
	uint32_t new_val = old_val & 0b11111110000000000000000000000000;
	new_val = new_val | (z << 22);
	new_val = new_val | (y << 12);
	new_val = new_val | (x << 2 );
	new_val = new_val | pallete;
	*img_ptr = new_val;

	return 1;

}

uint32_t _imagePaletteSet(uint32_t image, uint32_t palette){
	uint32_t * img_ptr = (uint32_t *) &BACKGROUND_CTRL_0 + (image * 0x4);
	uint32_t mask = 0xFFFFFFF0 | 0b1100;
	uint32_t old_val = *img_ptr & mask;
	*img_ptr = old_val | palette;
	return 1; 
}