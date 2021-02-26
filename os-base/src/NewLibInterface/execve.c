// OS does not provide processes. Minimal implementation
#include <errno.h>
#undef errno
extern int errno;
int _execve(char *name, char **argv, char **env) {
  errno = ENOMEM;
  return -1;   /* Always Fail */
}