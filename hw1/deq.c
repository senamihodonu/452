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


/*Appends a new node onto an end*/
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
  //increment list size
  r->len=r->len+1;
} else if(e==Tail){
  //allocate node
  Node new_node = deq_new();
  //create and last node
  Node last_node = r->ht[Head];
  //put data in new node
  new_node->data=d;
  //the next for the item inserted at the
  //end would be null
  new_node->np[Tail]=0;
  //if list is empty, the inserted node 
  //is th head
  if((r->ht[Head])==0) {
    new_node->np[Head] = 0;
    r->ht[Head]=new_node;
    return;
  }
  //traverse till the last node
  while(last_node->np[Tail] != 0){
    last_node=last_node->np[Tail];
  }
  //the last node becomes the new node
  last_node->np[Tail]=new_node;
  //the last node is the previous of the
  //node indserted at the end
  new_node->np[Head] = last_node;
  //increment list size
  r->len=r->len+1;
}
}

/*Takes a node reference, starting direction and an
index and return by 0-base index, len unchanged*/
static Data ith(Rep r, End e, int i) { 

  int counter = 0;
  Node curr = r->ht[Head];
  if(i >= r->len){
    ERROR("IndexOutOfBoundsException: Index: %d, Size: %d\n", i, r->len);
  }
  if(e==Head){
    //if i = 0, return the head of the list
    if(i==0){
      return (r->ht[Head])->data;
    } else {
      while(curr != 0){
        if(counter == i){
          return (curr->data);
        }
        counter++;
        curr = curr->np[Tail];
      }
    }
  } else if(e==Tail){
      while(curr != 0){
          if(counter == (r->len)-i-1){
            return (curr->data);
          }
          counter++;
          curr = curr->np[Tail];
        }
  }
  return 0; 
}

/*get: return from an end, len--*/
static Data get(Rep r, End e) { 
  Data d = 0;
  if(e==Head){
    //if the head node is null
    //list is empty
    if(r->ht[Head] == 0){
      ERROR("empty list");
    }
    //current node
    Node head_node = r->ht[Head];
    //save the data before the node is deleted
    d = head_node->data;
    //unlink the head node
    r->ht[Head] = (r->ht[Head])->np[Tail];
    //free the head node
    free(head_node);
    //decrement list size
    r->len=r->len-1;

  } else if(e==Tail){
    if(r->ht[Head] != 0){
      if(r->ht[Head] == 0){
        r->ht[Head] = 0;
      } else {
        Node temp = r->ht[Head];
          //traverse till the last node
        while(temp->np[Tail]->np[Tail] != 0){
          temp=temp->np[Tail];
        }

        //unlink the tail node
        Node last_node = temp->np[Tail];
        temp->np[Tail] = 0;
        d = last_node->data;
        free(last_node);
        r->len=r->len-1;
      }
    }
  }
  return d; 
}

/*rem: return by == comparing, len-- (iff found)*/
static Data rem(Rep r, End e, Data d) { 
  if(r->ht[Head] == 0){
    ERROR("empty list");
  }

  Node curr = r->ht[Head];
  Node next;
  while(curr->np[Tail] != 0){
    if(curr->data == d){
        next = curr->np[Tail]; 
        free(curr);
        curr = next;
    } else {
      curr = curr->np[Tail];
    }
  }




  return 0; }

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
