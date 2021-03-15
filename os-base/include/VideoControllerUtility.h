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

/* Prints text to screen if in text mode. 
   Returns 1 if success
   Returns -1 if failure
*/
uint32_t _fillText(char *buff, uint32_t size);

/* Sets specified layers background
   Returns 1 if success
   Returns -1 if failure
*/
uint32_t _fillImage(uint32_t background, uint8_t* buff, uint32_t size);

/* Sets the palette information for the specified palette
 
*/
uint32_t _fillPalette(uint32_t background, uint32_t* buff);

/* Sets image and palette

*/
uint32_t _imageSet(uint32_t image, uint32_t x, uint32_t y, uint32_t z, uint32_t palette);

/* Sets image with old palette

*/
uint32_t _imageMove(uint32_t image, uint32_t x, uint32_t y, uint32_t z);

uint32_t _imagePaletteSet(uint32_t image, uint32_t palette);

uint32_t _clearText();



#endif