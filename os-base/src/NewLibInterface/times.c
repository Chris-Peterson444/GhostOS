// OS does not provide processes. Minimal implementation
#include <errno.h>
#undef errno
extern int errno;
int _times(struct tms *buf) {
	errno = EACCES;
	return -1;  /* Always fail */
}