// Building for firmware based system. Does not provide files. Minimal implementation
#include <sys/stat.h>
int _fstat(int file, struct stat *st) {
  st->st_mode = S_IFCHR;
  return 0;
}