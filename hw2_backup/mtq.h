#include "deq.h"

typedef void *MTQ;
typedef void *Data;

extern MTQ mtq_new();

extern void mtq_tail_put(Deq q, Data d);

extern Data mtq_head_get(Deq q);