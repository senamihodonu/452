#include <stdio.h>
#include <stdlib.h>

#include "deq.h"

int main() {
  Deq q=deq_new();

  //Testing empty list
  deq_head_put(q, "1");
  deq_tail_put(q, "2");
  deq_tail_put(q, "3");
  deq_tail_put(q, "4");
  deq_head_put(q, "5");
  deq_len(q);
  // deq_head_ith(q, 0);
  char *s=deq_str(q,0);
  printf("%s\n",s);
  //printf("%d\n",deq_len(q));
  printf("%s\n",(char*)deq_tail_ith(q, 5));
  free(s);

  deq_del(q,0);
  return 0;
}
