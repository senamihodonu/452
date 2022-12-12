#ifndef BALLOC_H
#define BALLOC_H

#include <stdint.h>
#include <stddef.h>

#define MAX_ORDER       12
#define MIN_ORDER       0   

/* the order ranges 0..MAX_ORDER, the largest memblock is 2**(MAX_ORDER) */
#define POOLSIZE        (1 << MAX_ORDER)

/* blocks are of size 2**i. */
#define BLOCKSIZE(i)    (1 << (i))

/* the address of the buddy of a block from freelists[i]. */
#define _MEMBASE        ((uintptr_t)BUDDY->pool)
#define _OFFSET(b)      ((uintptr_t)b - _MEMBASE)
#define _BUDDYOF(b, i)  (_OFFSET(b) ^ (1 << (i)))
#define BUDDYOF(b, i)   ((Balloc)( _BUDDYOF(b, i) + _MEMBASE))


typedef void *Balloc;

typedef struct buddy {
  Balloc freelist[MAX_ORDER + 2];  // one more slot for first block in pool
  uint8_t pool[POOLSIZE];
  int buddySize;
  int lower;
  int upper;
} buddy_t;

extern Balloc bnew(unsigned int size, int l, int u);
extern void *balloc(Balloc pool, unsigned int size);
extern void bfree(Balloc pool, void *mem);
extern unsigned int bsize(Balloc pool, void *mem);
extern void bprint(Balloc pool);

#endif /* BALLOC_H_ */
