#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#include "lawn.h"
#include "mole.h"
#include "deq.h"
#include "thread.h"

// static pthread_mutex_t mutex;

//struct for produces parameters
typedef struct arg_struct
{
   Deq q_arg;
   Lawn lawn_arg;
} arg_struct;

void *produce(void *a) {
  arg_struct* args  = (arg_struct*)a;
  // void **arg=a;
  // Deq q = (Deq)arg[0];
  // Lawn l = (Lawn)arg[1];
  Deq q = args->q_arg;
  Lawn l = args->lawn_arg;
  // Deq q = deq_new();
  // Lawn l = lawn_new(0,0);
  // args->lawn_arg = l;
  // args->q_arg = q;
  // char *s=deq_str(q,0);
  // int size = deq_len(q);
  // printf("list --> [ %s ], size = %d\n",s, size);

  printf("produce\n");
 
  
  deq_head_put(q, mole_new(l,0,0));
  printf("produce2\n");
  return 0;
}

void *consume(void *a) {
  arg_struct* args  = (arg_struct*)a;
  // void **arg=a;
  // Deq q = (Deq)arg[0];
  Deq q = args->q_arg;
  mole_whack(deq_head_get(q));
  return 0;
}

 
// static Mole produce(Lawn l) { return mole_new(l,0,0); }
// static void consume(Mole m) { mole_whack(m); }

int main() {
  // pthread_mutex_init(&mutex,0);
  srandom(time(0)); //random number generator
  const int n=100;
  // pthread_t tids[n];
  // pthread_t tids2[n];
  //allocate memory for thread arguments
  arg_struct* args = (struct arg_struct *) malloc(sizeof(struct arg_struct));

  Lawn lawn=lawn_new(0,0);
  Deq q=deq_new(20);
  
  args->lawn_arg = lawn;
  args->q_arg = q;

  Pt thread = make_thread(n);
  Pt thread2 = make_thread(n);
  // Thread thread2 = make_thread(n);
  // printf("Sad\n");

  create_thread(thread,&produce,(void*)args, n);

  create_thread(thread2,(void*)consume,(void*)args, n);

  joining(thread,n);

  joining(thread2,n);


  // for (int i=0; i<n; i++){
  //   pthread_create(&tids[i],0,(void*)produce,(void*)args);
  // }


  // create_thread(&tids2,(void*)consume,(void*)args, n);
  // joining(tids2);
    
  // for (int i=0; i<n; i++){
  //   pthread_join(tids[i],0);
  // }

  // for (int i=0; i<n; i++){
  //   pthread_create(&tids2[i],0,(void*)consume,(void*)args);
  // }
    
  // for (int i=0; i<n; i++){
  //   pthread_join(tids2[i],0);
  // }




  // Lawn lawn=lawn_new(0,0);
  
  // Deq q=deq_new();

  // deq_head_put(q, produce(lawn));


  // for (int i=1; i<=n; i++)
  //   // consume(produce(lawn));
  //   consume((Mole*) deq_head_get(q));
  lawn_free(lawn);
  free(q);
  free(args);
  free(thread);
  free(thread2);

  // pthread_mutex_destroy(&mutex);

  return 0;
}
