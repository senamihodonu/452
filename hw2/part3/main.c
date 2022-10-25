#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "lawn.h"
#include "mole.h"
#include "deq.h"
#include "thread.h"

/**
 * @brief program modified to use separate threads for 
 * each produce and consume call
 * 
 */

typedef struct arg_struct
{
   Deq q_arg;
   Lawn lawn_arg;
} arg_struct;

void *produce(void *a) {
  arg_struct* args  = (arg_struct*)a;
  Deq q = args->q_arg;
  Lawn l = args->lawn_arg;
  deq_tail_put(q, mole_new(l,0,0));
  return 0;
}

void *consume(void *a) {
  arg_struct* args  = (arg_struct*)a;
  Deq q = args->q_arg;
  mole_whack(deq_head_get(q));
  return 0;
}


int main() {
  printf("Part#3\n");
  srandom(time(0)); //random number generator
  const int n=4;
  arg_struct* args = (struct arg_struct *) malloc(sizeof(struct arg_struct));

  Lawn lawn=lawn_new(0,0);
  Deq q=deq_new();
  
  args->lawn_arg = lawn;
  args->q_arg = q;

  Pt thread = make_thread(n);
  Pt thread2 = make_thread(n);
  
  create_thread(thread,(void*)produce,(void*)args, n);
  create_thread(thread2,(void*)consume,(void*)args, n);
  
  joining(thread,n);
  joining(thread2,n);



  lawn_free(lawn);
  deq_del(q,0);
  free(args);
  free(thread);
  free(thread2);

  return 0;
}
