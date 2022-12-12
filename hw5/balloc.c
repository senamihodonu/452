#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <stddef.h>
#include "balloc.h"
#include "utils.h"
/*
* Implementation of a buddy system algorithm
* @author Senami Hodonu
*/

long int alloc_lower_limit = 0;
long int alloc_upper_limit = 0;
buddy_t * BUDDY = 0;
/**
 * @brief constructs and returns a new allocator
 * 
 * @param size - total number of bytes that can be allocated
 * @param l - the smallest allocation exponent (i.e 2^l bytes)
 * @param u - the largest allocation exponent (i.e 2^u bytes)
 * @return Balloc 
 */
extern Balloc bnew(unsigned int size, int l, int u) {
  long int alloc_lower_limit = e2size(l);
  long int alloc_upper_limit = e2size(u);

  printf("size = %d\n", size);
  printf("size to a power of 2 is %d\n", size2e(size));
  printf("the upper limit is (e2size(u)) = %ld\n", alloc_upper_limit);
  printf("the lower limit is (e2size(l)) = %ld\n", alloc_lower_limit);
  //if there's a larger request, bnew fails
  if(size2e(size) > e2size(u)){
      perror("space not available"), exit (EXIT_FAILURE);

  } 
  //if size is less than the smallest allocation 
  //possible, allocate the lower limit
  if(size2e(size) < e2size(l)){
      size = e2size(l);
  } else {
    size = size2e(size);
  }

  Balloc new = mmalloc(size);
  buddy_t* kaboom = (buddy_t*)new;
  kaboom->buddySize = size;
  kaboom->lower = alloc_lower_limit;
  kaboom->upper = alloc_upper_limit;


  BUDDY = new;
  memset(BUDDY, 0, sizeof(buddy_t));
  BUDDY->freelist[u] = BUDDY->pool;
  
  return new;

}

/**
 * @brief requests a block of "size" bytes from an allocator
 * 
 * @param pool 
 * @param size 
 * @return void* 
 */
Balloc balloc(Balloc pool, unsigned int size) {

  // calculate minimal order for this size
  int i = 0;
  while (BLOCKSIZE(i) < size + 1) // one more byte for storing order
    i++;

  int order = i = (i < alloc_lower_limit) ? alloc_lower_limit : i;

  // level up until non-null list found
  while(1){
    if (i > MAX_ORDER)
      return NULL;
    if (BUDDY->freelist[i])
      break;
    i++;
  }

  // remove the block out of list
  Balloc block = BUDDY->freelist[i];
  BUDDY->freelist[i] = *(Balloc*) BUDDY->freelist[i];

  // split until i == order
  while (i-- > order) {
    Balloc buddy = BUDDYOF(block, i);
    BUDDY->freelist[i] = buddy;
  }

  // store order in previous byte
  *((uint8_t*) (block - 1)) = order;
  return block;
}

/**
 * @brief deallocates a block of memory
 * 
 * @param pool 
 * @param mem 
 */
void bfree(Balloc pool, void *mem) {

}

/**
 * @brief returns the size of an allocation (not the rquest size)
 * 
 * @param pool 
 * @param mem 
 * @return unsigned int 
 */
extern unsigned int bsize(Balloc pool, void *mem);

static void print_list(int i) {

  printf("freelist[%d]: \n", i);

  Balloc *p = &BUDDY->freelist[i];
  while (*p != NULL) {
    printf("    0x%08lx, 0x%08lx\n", (uintptr_t) *p, (uintptr_t) *p - (uintptr_t) BUDDY->pool);
    p = (Balloc*) *p;
  }
}

/**
 * @brief writes a textual representation of an allocator tp stout: 
 * a valuable debugging tool
 * 
 * @param pool 
 */
void bprint(Balloc pool) {
  int i;
  printf("========================================\n");
  printf("Memory pool starts @ 0x%08x\n", (unsigned int) (uintptr_t) BUDDY->pool);

  for (i = 0; i <= MAX_ORDER; i++) {
    print_list(i);
  }
}
