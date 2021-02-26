// Firmware based os. No file support. Minimal implementation
#include <errno.h>
#undef errno
extern int errno;
int _open(const char *name, int flags, int mode) {
  errno = ENOSYS;
  return -1;  /* ALways fail */
}