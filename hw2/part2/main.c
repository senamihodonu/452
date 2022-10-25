
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "lawn.h"
#include "mole.h"
#include "deq.h"
/**
 * @brief progam modified to communicate through a deq
 * @author senami hodonu
 */

static Mole produce(Lawn l) { return mole_new(l,0,0); }
static void consume(Mole m) { mole_whack(m); }

int main() {
  srandom(time(0));
  const int n=10;
  Lawn lawn=lawn_new(0,0);
  Deq q=deq_new();
  //the produce function adds a mole
  //to the front of the deq
  for (int i=1; i<=n; i++)
    deq_head_put(q, produce(lawn));
  //the consume function removes a mole
  //to the tail of the deq
  for (int i=1; i<=n; i++)
    consume((Mole*) deq_tail_get(q));

  lawn_free(lawn);
  deq_del(q,0);
}