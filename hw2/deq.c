#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<pthread.h>

#include "deq.h"
#include "error.h"
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
  int size
} *Rep;

static Rep rep(Deq q) {
  if (!q) ERROR("zero pointer");
  return (Rep)q;
}

/*Appends a new node onto an end (Head/Tail)*/
static void put(Rep r, End e, Data d) {
//allocate node
Node new_node = deq_new(r->size);
pthread_mutex_lock(&r->lock); ///////////////////////
while(r->len >= r->size){
  pthread_cond_wait(&r->condv,&r->lock);
}
// pthread_cond_signal(&r->condv);
if(e==Head){

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
  //create and last node
  Node last_node = r->ht[Head];
  //put data in new node
  new_node->data=d;
  //the next for the item inserted at the
  //end would be null
  new_node->np[Tail]=0;
  //if list is empty, the inserted node 
  //is the head node and the tail node
  if((r->ht[Head])==0) {
    new_node->np[Head] = 0; //the next for the inserted node is null
    r->ht[Head]=new_node;
    r->ht[Tail]=new_node;
    //increment list size
    r->len=r->len+1;
    return;
  }
  //traverse till the node before last
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
pthread_mutex_unlock(&r->lock);
pthread_cond_signal(&r->condv);
}

/*Takes a node reference, starting direction and an
index and return by 0-base index, len unchanged*/
static Data ith(Rep r, End e, int i) { 
  int counter = 0;
  Node curr = r->ht[Head];
  while(r->len >= r->size){
    pthread_mutex_lock(&r->lock); ///////////////////////
  }

  //if index is greater or equal to the size of the list
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
  pthread_mutex_unlock(&r->lock); ///////////////////////
  return 0; 
}

/*get: return the top data from an end, len--*/
static Data get(Rep r, End e) { 
  pthread_mutex_lock(&r->lock);
  while (r->len == 0){
    pthread_cond_wait(&r->condv,&r->lock);
  }
  Data d = 0;
  //if the head node is null, the list is empty
  if(r->ht[Head] == 0){
    ERROR("empty list(#el00)!");
  }
  //current node
  Node curr = r->ht[Head];

  if(e==Head){
    //save the data before the node is deleted
    d = curr->data;
    //unlink the head node
    r->ht[Head] = (r->ht[Head])->np[Tail];
    //free the head node
    free(curr);
    printf("head node removed(#hn00)!\n");
    //decrement list size
    r->len=r->len-1;
  } else if(e==Tail){
    if(curr != 0){
      //if the next of the head node is null
      //free the head node
      if(curr->np[Tail] == 0){
        d = curr->data;
        r->ht[Head] = 0;
        r->len=r->len-1;
        free(curr);
       printf("tail node deleted(#tn00)!\n");
      } else {
        Node temp = r->ht[Head];
        while(temp->np[Tail]->np[Tail]){
          temp = temp -> np[Tail];
        }

        Node last_node = temp->np[Tail];
        d = last_node->data;
        temp->np[Tail] = 0;
        free(last_node);
        printf("tail node deleted(#tn01)!\n");
        //decrement list size
        r->len=r->len-1;
      }
    }
  }
  pthread_mutex_unlock(&r->lock);
  pthread_cond_signal(&r->condv);
  return d; 
}

/*rem: return by == comparing, len-- (iff found)*/
static Data rem(Rep r, End e, Data d) {
  pthread_mutex_lock(&r->lock); ///////////////////////
    Node curr = r->ht[Head]; //current pointer
    //if the head node is null, the list is empty
    if(curr == 0){
      ERROR("empty list");
    }
    //when list has only one node
    if (curr->np[Tail] == 0) {
        if (curr->data == d) {
            free(curr);
            r->ht[Head] = 0;
            r->len=r->len-1;
        } else {
            printf("No match found in list\n");
        }
        return d;
    }

    if(e==Head){
        // data is at the head node, make head next 
        // as head and delete previous head
        if(curr->data == d) {
          Node nodeToDelete = r->ht[Head];
          r->ht[Head] = (r->ht[Head])->np[Tail];
          free(nodeToDelete);
          r->len=r->len-1;
        } else {
          // traverse to the node previous to the node 
          // with value equal to key, and adjust links 
          while(curr) {
            if(curr->np[Tail]->data == d) {
              Node nodeToDelete = curr->np[Tail];
              curr->np[Tail] = curr->np[Tail]->np[Tail];
              free(nodeToDelete);
              r->len=r->len-1;
              break; 
            } else {
              curr = curr->np[Tail];
            }
          }
        }
    } else {
        Node prev = 0;
        Node nodeToDelete = 0;
        //Keep track of previous node
        while (curr && curr->np[Tail] != 0) {
            if ((curr->np[Tail])->data == d) {
                prev = curr;
                nodeToDelete = curr->np[Tail];
            }
            curr = curr->np[Tail];
        }

        if (prev != 0){
            prev->np[Tail] = nodeToDelete->np[Tail];
            free (nodeToDelete);
            r->len=r->len-1;
        } else {
                //if last node is the head
                if ((r->ht[Head])->data == d) {
                curr = r->ht[Head];
                r->ht[Head] = curr->np[Tail];
                free (curr);
                r->len=r->len-1;
            } else {
                printf("No match found in list\n");
            }
          }
    }
    pthread_mutex_unlock(&r->lock); ///////////////////////
    return d;
  }

extern Deq deq_new(int size) {
  Rep r=(Rep)malloc(sizeof(*r));
  if (!r) ERROR("malloc() failed");
  pthread_mutex_init(&r->lock, 0); //initialize lock
  pthread_cond_init(&r->condv,0); //initialize condition variable
  r->ht[Head]=0;
  r->ht[Tail]=0;
  r->len=size;
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
