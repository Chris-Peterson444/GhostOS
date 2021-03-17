/* 
From https://sourceware.org/newlib/

Increase program data space. As malloc and related functions depend on this, it is useful to have a working implementation. 
The following suffices for a standalone system; it exploits the symbol _end automatically defined by the GNU linker. 

*/

/* 

Heap is situated on the opposite end of stack. Allocate until 

*/

// Do I want to use this instead of pointing to __stack_top?
// is __stack_top a static? probably right?

#include <errno.h>
#include "Threads.h"
#undef errno
extern int  errno;

// register char *stack_ptr asm ("sp");
extern ThreadQueueManager TQManager;


void * _sbrk(int incr) {
  extern char _heapbase;           /* Defined by the linker */
  static char *heap_end;
  char *prev_heap_end;
 
  if (heap_end == 0) {
    heap_end = &_heapbase;
  }
  prev_heap_end = heap_end;
  if (heap_end + incr > TQManager.mainStackPointer) {
    errno = ENOMEM;
    return  (void *) -1;

    // return (void*)heap_end;
    // To-do
    // write (1, "Heap and stack collision\n", 25);
    // abort ();
  }

  heap_end += incr;
  return (void *) prev_heap_end;
}