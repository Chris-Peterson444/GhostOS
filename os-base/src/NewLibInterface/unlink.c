// Firmware based os. No file support. Minimal implementation
#include <errno.h>
#undef errno
extern int errno;
int _unlink(char *name) {
  errno = ENOENT;
  return -1; /* Always fail */
}