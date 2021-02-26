// Firmware based os. No file support. Minimal implementation
#include <errno.h>
#undef errno
extern int errno;
int _link(char *old, char *new) {
  errno = EMLINK;
  return -1; /* Always fail */
}