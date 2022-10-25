# Homework #2: Whack-a-Mole and Race Conditions

* Senami Hodonu
* Class: CS 452


## Overview

The goal of this assignment was to understand and practice single-process 
multi-thread (MT) programming, including the design and implementation of 
MT-safe functions and data structures. This goal was acheived by implementing
a Whack-a-Mole module. A partial implementation of the module was provided. 
The completed program was tested using valgrind to make sure no memory leaks 
were present in the program. 

## Manifest
The project directory is composed of the following files which different
implementaion broken down to different folders:
.
├── part2 (#1 & #2 in project documentation)
│   ├── deq.c
│   ├── deq.h
│   ├── error.h
│   ├── fltk.supp
│   ├── GNUmakefile
│   ├── lawn.c
│   ├── lawn.h
│   ├── lawnimp.cc
│   ├── lawnimp.h
│   ├── linkage.h
│   ├── main.c
│   ├── mole.c
│   ├── mole.h
│   └── vg
├── part3 (#2 in project documentation)
│   ├── deq.c
│   ├── deq.h
│   ├── error.h
│   ├── fltk.supp
│   ├── GNUmakefile
│   ├── lawn.c
│   ├── lawn.h
│   ├── lawnimp.cc
│   ├── lawnimp.h
│   ├── linkage.h
│   ├── main.c
│   ├── mole.c
│   ├── mole.h
│   ├── thread.c
│   ├── thread.h
│   └── vg
├── part4 (#4 & #5 in project documentation)
│   ├── deq.c
│   ├── deq.h
│   ├── error.h
│   ├── fltk.supp
│   ├── GNUmakefile
│   ├── lawn.c
│   ├── lawn.h
│   ├── lawnimp.cc
│   ├── lawnimp.h
│   ├── linkage.h
│   ├── main.c
│   ├── mole.c
│   ├── mole.h
│   ├── thread.c
│   ├── thread.h
│   └── vg
└── README.md

3 directories, 47 files

## Building the project

To build this program, in the directory containing the program, the make 
command is run:

$ make

After a successful build, the following command is issued to run the main.c, 
which contains the program driver:

$ ./wam

The following command can be ran to build and run the program at the same 
time:

$ make run


## Testing

The provided valgrind script was run to check for memory leaks. There were no 
registered memory leaks related to any of the implementation.

$ vg

Below is the summary of the report from running the aforemention command.

==51671== 
==51671== HEAP SUMMARY:
==51671==     in use at exit: 710,858 bytes in 1,086 blocks
==51671==   total heap usage: 13,775 allocs, 12,689 frees, 2,759,137 bytes allocated
==51671== 
==51671== 22 bytes in 1 blocks are still reachable in loss record 37 of 222
==51671==    at 0x4C37135: malloc (vg_replace_malloc.c:381)
==51671==    by 0x4011148: UnknownInlinedFun (rtld-malloc.h:56)
==51671==    by 0x4011148: _dl_new_object (dl-object.c:196)
==51671==    by 0x400B796: _dl_map_object_from_fd (dl-load.c:1014)
==51671==    by 0x400E6B4: _dl_map_object (dl-load.c:2273)
==51671==    by 0x4019188: dl_open_worker_begin (dl-open.c:532)
==51671==    by 0x6162183: _dl_catch_exception (in /usr/lib64/libc-2.28.so)
==51671==    by 0x4018AC6: dl_open_worker (dl-open.c:793)
==51671==    by 0x6162183: _dl_catch_exception (in /usr/lib64/libc-2.28.so)
==51671==    by 0x4018D10: _dl_open (dl-open.c:900)
==51671==    by 0x65E71E9: dlopen_doit (in /usr/lib64/libdl-2.28.so)
==51671==    by 0x6162183: _dl_catch_exception (in /usr/lib64/libc-2.28.so)
==51671==    by 0x6162242: _dl_catch_error (in /usr/lib64/libc-2.28.so)
==51671== 
==51671== 1,199 bytes in 1 blocks are still reachable in loss record 197 of 222
==51671==    at 0x4C3BE4B: calloc (vg_replace_malloc.c:1328)
==51671==    by 0x4010F56: UnknownInlinedFun (rtld-malloc.h:44)
==51671==    by 0x4010F56: _dl_new_object (dl-object.c:89)
==51671==    by 0x400B796: _dl_map_object_from_fd (dl-load.c:1014)
==51671==    by 0x400E6B4: _dl_map_object (dl-load.c:2273)
==51671==    by 0x4019188: dl_open_worker_begin (dl-open.c:532)
==51671==    by 0x6162183: _dl_catch_exception (in /usr/lib64/libc-2.28.so)
==51671==    by 0x4018AC6: dl_open_worker (dl-open.c:793)
==51671==    by 0x6162183: _dl_catch_exception (in /usr/lib64/libc-2.28.so)
==51671==    by 0x4018D10: _dl_open (dl-open.c:900)
==51671==    by 0x65E71E9: dlopen_doit (in /usr/lib64/libdl-2.28.so)
==51671==    by 0x6162183: _dl_catch_exception (in /usr/lib64/libc-2.28.so)
==51671==    by 0x6162242: _dl_catch_error (in /usr/lib64/libc-2.28.so)
==51671== 
==51671== LEAK SUMMARY:
==51671==    definitely lost: 0 bytes in 0 blocks
==51671==    indirectly lost: 0 bytes in 0 blocks
==51671==      possibly lost: 0 bytes in 0 blocks
==51671==    still reachable: 1,221 bytes in 2 blocks
==51671==         suppressed: 709,637 bytes in 1,084 blocks
==51671== 
==51671== For lists of detected and suppressed errors, rerun with: -s
==51671== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)


## Known Bugs

The gdb debugger was used to debug segmentation faults that arose during the
program implemention.
 

## Reflection
The biggest challenge on this project was on memory allocation in the thread.c
class. A segmentation fault was resulting from an improper allocation for the
pthread array. The problem  was that the allocation was not accounting for the 
number of elements. To solve this, the malloc was multiplied by the number of 
elements in the array.


## Sources used

Class materials and pthread documentions


