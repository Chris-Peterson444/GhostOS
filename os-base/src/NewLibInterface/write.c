// Firmware based os. No file support. Minimal implementation

/*
From the https://sourceware.org/newlib/

Write to a file. libc subroutines will use this system routine for output to all files, including stdout—so if you need to generate any output,
 for example to a serial port for debugging, you should make your minimal write capable of doing this. 

 The following minimal implementation is an incomplete example; it relies on a outbyte subroutine (not shown; typically, 
 you must write this in assembler from examples provided by your hardware manufacturer) to actually perform the output. 


int _write(int file, char *ptr, int len) {
  int todo;

  for (todo = 0; todo < len; todo++) {
    outbyte (*ptr++);
  }
  return len;
}


*/

#include "VideoControllerMap.h"
#include <stdint.h>

void outbyte(char ch);


// Newlib write stub
int _write(int file, char *ptr, int len) {
  int todo;

  for (todo = 0; todo < len; todo++) {
    outbyte (*ptr++);
  }
  return len;
}

//Print text to screen like a terminal
void outbyte(char ch){
	uint8_t * textData = (uint8_t *) &TEXT_DATA;
	static uint8_t XPos = 0, YPos = 0;
	const uint8_t CharsPerRow = 64, RowsPerScreen = 36;

	switch(ch){

		case '\n':
			XPos = 0;
			YPos = (YPos + 1) % RowsPerScreen;
			break;
		case '\r':
			XPos = 0;
			break;
		case '\b':
			XPos--;
			break;
		default:
			textData[XPos + YPos*RowsPerScreen] = ch;
			XPos++;
			if( CharsPerRow <= XPos){
				XPos = 0;
				YPos = (YPos + 1) % RowsPerScreen;
			}
			break;
	}
}