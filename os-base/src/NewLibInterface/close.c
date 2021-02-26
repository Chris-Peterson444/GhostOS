// Firmware based os. No file support. Minimal implementation
#include <errno.h>
#undef errno
extern int errno;
int _close(int file) {
	errno = EBADF;
	return -1;  /* Always fail */
}