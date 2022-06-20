#ifndef BUFFER_H
#define BUFFER_H

enum {max=5};			// maximum capacity of buffer

typedef int (*Busy)();
  
extern int full();
extern int empt();

extern int get();
extern void put(int data);

#endif
