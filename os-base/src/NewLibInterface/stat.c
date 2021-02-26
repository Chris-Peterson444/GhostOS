// Firmware based os. No file support. Minimal implementation
#include <sys/stat.h>
int _stat(const char *file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}