Homework #5: Memory Hole

* Senami Hodonu
* Class: CS 452


## Overview

The goal of this assignment is to develop a memory allocator, using a scheme known
as the Buddy System.

## Manifest
The project directory is composed of the following files which different
implementaion broken down to different folders:
.
.
├── balloc.c
├── balloc.h
├── bitmap.c
├── bitmap.h
├── freelist.c
├── freelist.h
├── GNUmakefile
├── help.txt
├── main.c
├── README.md
├── utils.c
├── utils.h
├── utils.h.gch
└── wrapper.c

0 directories, 14 files

## Building the project

To build this program, in the directory containing the program, the make 
command is run:

$ make

After a successful build, the following command is issued to run the main.c, 
which contains the program driver:

$ ./buddy


## Testing
There were no observed leaks in the program. Valgrind summary below.

==1615601== HEAP SUMMARY:
==1615601==     in use at exit: 1,024 bytes in 1 blocks
==1615601==   total heap usage: 1 allocs, 0 frees, 1,024 bytes allocated
==1615601== 
==1615601== LEAK SUMMARY:
==1615601==    definitely lost: 0 bytes in 0 blocks
==1615601==    indirectly lost: 0 bytes in 0 blocks
==1615601==      possibly lost: 0 bytes in 0 blocks
==1615601==    still reachable: 1,024 bytes in 1 blocks
==1615601==         suppressed: 0 bytes in 0 blocks
==1615601== Rerun with --leak-check=full to see details of leaked memory
==1615601== 
==1615601== For lists of detected and suppressed errors, rerun with: -s
==1615601== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)

## Reflection
This was a very challenging project. 


## Sources used
https://arjunsreedharan.org/post/148675821737/memory-allocators-101-write-a-simple-memory
https://github.com/matianfu/buddy/blob/master/buddy.c
https://www.geeksforgeeks.org/buddy-memory-allocation-program-set-1-allocation/
https://github.com/evanw/buddy-malloc/blob/master/buddy-malloc.c
https://people.kth.se/~johanmon/ose/assignments/buddy.pdf
https://www.interviewcake.com/concept/java/bit-shift
https://stackoverflow.com/questions/948654/what-do-these-c-operators-mean
https://research.cs.vt.edu/AVresearch/MMtutorial/buddy.php
https://www.geeksforgeeks.org/fast-exponention-using-bit-manipulation/
https://www.kernel.org/doc/gorman/html/understand/understand009.html
https://moss.cs.iit.edu/cs351/slides/slides-malloc.pdf
https://stackoverflow.com/questions/40726269/how-to-implement-a-bitset-in-c


