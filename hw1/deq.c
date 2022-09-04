#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deq.h"
#include "error.h"

// indices and size of array of node pointers
typedef enum {Head,Tail,Ends} End;

typedef struct Node {
  struct Node *np[Ends];		// next/prev neighbors
  Data data;
} *Node;

typedef struct {
  Node ht[Ends];			// head/tail nodes
  int len;
} *Rep;

static Rep rep(Deq q) {
  if (!q) ERROR("zero pointer");
  return (Rep)q;
}

static void put(Rep r, End e, Data d) {
if(e==Head){
  //allocate node
  Node new_node=deq_new();
  //put in data
  new_node->data=d;
  //make next of new node as head and previous null
  new_node->np[Tail] = r->ht[Head];
  new_node->np[Head] = 0;
  //change prev of head node to new node
  if((r->ht[Head])!=0) (r->ht[Head])->np[Head]=new_node;
  //move the head to point to the new node
  r->ht[Head] = new_node;
//  free(r);
} else if(e==Tail){
  //allocate node
  Node new_node = deq_new();
  
  new_node->data=d;

  new_node->np[Tail]=0;
  new_node->np[Head]=0;

  if(r->ht[Head] == 0){
    new_node->np[Head] = new_node;
    new_node->np[Tail]= new_node;
  } else {
      (new_node->np[Tail])->np[Head] = new_node;
      new_node->np[Head]=new_node->np[Tail];
      new_node->np[Tail]=new_node;
  }

}

}
static Data ith(Rep r, End e, int i) { return 0; }
static Data get(Rep r, End e) { return 0; }
static Data rem(Rep r, End e, Data d) { return 0; }

extern Deq deq_new() {
  Rep r=(Rep)malloc(sizeof(*r));
  if (!r) ERROR("malloc() failed");
  r->ht[Head]=0;
  r->ht[Tail]=0;
  r->len=0;
  return r;
}

extern int deq_len(Deq q) { return rep(q)->len; }

extern void deq_head_put(Deq q, Data d) {        put(rep(q),Head,d); }
extern Data deq_head_get(Deq q)         { return get(rep(q),Head); }
extern Data deq_head_ith(Deq q, int i)  { return ith(rep(q),Head,i); }
extern Data deq_head_rem(Deq q, Data d) { return rem(rep(q),Head,d); }

extern void deq_tail_put(Deq q, Data d) {        put(rep(q),Tail,d); }
extern Data deq_tail_get(Deq q)         { return get(rep(q),Tail); }
extern Data deq_tail_ith(Deq q, int i)  { return ith(rep(q),Tail,i); }
extern Data deq_tail_rem(Deq q, Data d) { return rem(rep(q),Tail,d); }

extern void deq_map(Deq q, DeqMapF f) {
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail])
    f(n->data);
}

extern void deq_del(Deq q, DeqMapF f) {
  if (f) deq_map(q,f);
  Node curr=rep(q)->ht[Head];
  while (curr) {
    Node next=curr->np[Tail];
    free(curr);
    curr=next;
  }
  free(q);
}

extern Str deq_str(Deq q, DeqStrF f) {
  char *s=strdup("");
  for (Node n=rep(q)->ht[Head]; n; n=n->np[Tail]) {
    char *d=f ? f(n->data) : n->data;
    char *t; asprintf(&t,"%s%s%s",s,(*s ? " " : ""),d);
    free(s); s=t;
    if (f) free(d);
  }
  return s;
}
