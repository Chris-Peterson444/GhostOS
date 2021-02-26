/* 
From https://sourceware.org/newlib/

Increase program data space. As malloc and related functions depend on this, it is useful to have a working implementation. 
The following suffices for a standalone system; it exploits the symbol _end automatically defined by the GNU linker. 

*/

/* 

Currently minimal implementation. May need to modiy later and will update comment

*/

void * _sbrk(int incr) {
  // extern char _end;		 Defined by the linker 
  extern char _ebss;   /* Defined by the linker */
  extern char __stack_top; /* Defined by the linker */
  static char *heap_end;
  char *prev_heap_end;
 
  if (heap_end == 0) {
    heap_end = &_ebss;
  }
  prev_heap_end = heap_end;
  if (heap_end + incr > &__stack_top) {
    return (void*)heap_end;
    // To-do
    // write (1, "Heap and stack collision\n", 25);
    // abort ();
  }

  heap_end += incr;
  return (void *) prev_heap_end;
}