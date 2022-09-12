# Homework #1: Queue<Anon>

* Senami Hodonu
* Class: CS 452


## Overview

The goal of this assignment was to understand the design of, and complete 
the implementation of, a double-ended doubly-linked queue. A partial
implementation of the module was provided. The completed program was tested
using a developed test suite and valgrind was used to make sure no memory 
leaks were present in the program. 


## Building the project

To build this program, in the directory containing the program, the make 
command is issued:

$ make

After a successful build, the following command is issued to run the main.c, 
which contains the test suite.

$ ./deq

The following command can be ran to build and run the program at the same 
time:

$ make run


## Testing
The intial thought to test this program was to the Google Test framework for C.
A few scenarios were tested using this framework, however due to the growing 
complexity, this thought was abandoned and a total of 24 different tests where 
manually written to the main.c file to test this program. 

Running the valgrind command below, the program was tested for memory leaks.

$ valgrind --leak-check=full ./deq

Below is the summary of the report from running the aforemention command.

==6234==
==6234== HEAP SUMMARY:
==6234==     in use at exit: 0 bytes in 0 blocks
==6234==   total heap usage: 278 allocs, 278 frees, 11,040 bytes allocated
==6234==
==6234== All heap blocks were freed -- no leaks are possible
==6234==
==6234== For lists of detected and suppressed errors, rerun with: -s
==6234== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

## Known Bugs
There are no known bugs at the moment, however I believe to fully prove the
sustainabilty of this program, further testing scenarios should be explored.

The gdb debugger was minimally used for this program as there were not a 
substantial need for it.
 

## Reflection
This project served a huge refresher for me for the C language. Many of the 
concepts required some research to fully grasp and understand. My major concern 
while working on this project was my limited use of the tail pointer in my imple-
mentations. I feel like I could have used it more but I kept running into walls 
that caused me to explore alternative solutions.

For me, knowing and understanding the algorithms for these functions was not the
main issue. Working with and understanding pointers however was a little challenging 
for me and would require further practice to fully master.


## Sources used

https://stackoverflow.com/questions/7604762/finding-and-removing-the-last-occurrence-of-an-element-in-a-singly-linked-list
https://www.alphacodingskills.com/ds/notes/doubly-linked-list-delete-first-node-by-key.php
https://www.alphacodingskills.com/ds/notes/linked-list-delete-first-node-by-key.php

[Here is some help creating links](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet#links)
