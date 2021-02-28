#ifndef SYSCALLS_H
#define SYSCALLS_H 

#include <stdint.h>
#include "SystemCallCodes.h"

uint8_t  _getControllerStatus();
uint32_t _setBackground();
uint32_t _setPalette();
uint32_t _renderSprite();
uint32_t _graphicsMode(uint32_t mode);
uint32_t _printText();
uint32_t _setRefreshRate(uint32_t rate);
uint32_t _sleep(uint32_t milliseconds);

#endif