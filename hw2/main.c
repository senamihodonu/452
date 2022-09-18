#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "lawn.h"
#include "mole.h"
#include "deq.h"
 
static Mole produce(Lawn l) { return mole_new(l,0,0); }
static void consume(Mole m) { mole_whack(m); }

int main() {
  srandom(time(0));
  const int n=4;
  Lawn lawn=lawn_new(0,0);
  

  Deq q=deq_new();

  deq_head_put(q, produce(lawn));
  deq_head_put(q, produce(lawn));
  deq_head_put(q, produce(lawn));


  for (int i=1; i<=n; i++)
    // consume(produce(lawn));
    consume((Mole*) deq_head_get(q));
  lawn_free(lawn);
}
