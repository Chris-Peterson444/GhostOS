// Firmware based os. No file support. Minimal implementation
#include <errno.h>
#undef errno
extern int errno;
int _read(int file, char *ptr, int len) {
  return 0;
}