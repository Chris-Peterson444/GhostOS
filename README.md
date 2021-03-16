# GhostOS
GhostOS is a basic operating system built for a [RISC-V console simulator](https://github.com/UCDClassNitta/riscv-console "Up to date version") written by Professor Nitta. The last version this was designed for was commit [f5c7533](https://github.com/UCDClassNitta/riscv-console/tree/f5c7533182be7ab0a7fed1e7797ade2f2ff6a4ff "Most recent compatible version"). 



## Building
To build everything run:
```
make
```
This will just call the individual makefiles for each the operating system, the library/API, and the application.

## Operating system
To build the operating system
```
cd os-base/
make
```
Inside the [Makefile](os-base/Makefile) you can define DEBUG mode to allow for better debugging, or undefine it for optimizations.

## Application
To build the application
```
cd application-test/
make
```

The application is just a simple showcase that everything in the API works. Similar to the OS, inside the [Makefile](application-test/Makefile) you can define DEBUG mode to allow for better debugging, or undefine it for optimizations.

Additionally, if DEBUG mode is defined then the application will build the library files directly from the object files in `lib/obj/`, otherwise it will link using the .a library file found in `lib/bin/`.   

### Newlib support
The library provides integration for the [Newlib C Standard Library](https://sourceware.org/newlib/) via the files found in [os-base/src/NewLibInterface](os-base/src/NewLibInterface). Given the linker script provided for the application, this should be fine to use as is, but you can provide a different implementation of \_sbrk that fits the application needs better.


## API/Library
To build the interface. run:
```
cd lib/
make
```

This will build the library file (found in `lib/bin/`) that can be linked in at compile time to the application. Doing this, however, will not allow for debugging the functions in the library code. Instead you can find all of the object files used in `/lib/obj/` and link them directly into the application. You can look through the application [Makefile](application-test/Makefile) for how this is done.
