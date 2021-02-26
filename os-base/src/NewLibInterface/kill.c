// OS does not provide processes. Minimal implementation.
#include <errno.h>
#undef errno
extern int errno;
int _kill(int pid, int sig) {
  errno = EINVAL;
  return -1; /* Always Fail */
}