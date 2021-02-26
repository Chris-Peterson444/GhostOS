// OS does not provide processes. Minimal implementation.
#include <errno.h>
#undef errno
extern int errno;
int _wait(int *status) {
  errno = ECHILD;
  return -1; /* Always fail */
}
