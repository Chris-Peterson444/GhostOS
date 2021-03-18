#ifndef SYSCALLS_H
#define SYSCALLS_H 

#include <stdint.h>
#include "SystemCallCodes.h"

uint32_t  _getControllerStatus();
uint32_t _setImage(uint32_t image, uint32_t x, uint32_t y, uint32_t z, uint32_t palette);
uint32_t _imageFill(uint32_t background, uint8_t* buff, uint32_t size);
uint32_t _setPalette(uint32_t background, uint32_t* buff);
uint32_t _moveImage(uint32_t image, uint32_t x, uint32_t y, uint32_t z);
uint32_t _setImagePalette(uint32_t image, uint32_t palette);
uint32_t _renderSprite();
uint32_t _graphicsMode(uint32_t mode);
uint32_t _printText(char * buff, uint32_t size);
uint32_t _setRefreshRate(uint32_t rate);
uint32_t _clearTextScreen();
uint32_t _getThreadManager();
uint32_t _getTimerTicks();


#endif