#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<pthread.h>

#include "deq.h"
#include "error.h"
#include "mtq.h"

/*
* Implementation of a double-ended doubly-linked queue
*/

// indices and size of array of node pointers
typedef enum {Head,Tail,Ends} End;

typedef struct Node {
  struct Node *np[Ends];		// next/prev neighbors
  Data data;
} *Node;

typedef struct {
  Node ht[Ends];			// head/tail nodes
  int len;
  pthread_mutex_t lock;
  pthread_cond_t condv;
  int size;
} *Rep;

extern MTQ mtq_new() {
  Rep r=(Rep)malloc(sizeof(*r));
  if (!r) ERROR("malloc() failed");
  pthread_mutex_init(&r->lock, 0); //initialize lock
  pthread_cond_init(&r->condv,0); //initialize condition variable
  r->ht[Head]=0;
  r->ht[Tail]=0;
  r->len=0;
  return r;
}

extern void mtq_tail_put(Deq q, Data d) {      
      deq_tail_put(q, d);
}

extern Data mtq_head_get(Deq q) {
    return deq_head_get(q);
}


