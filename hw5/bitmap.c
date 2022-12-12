#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

#include "bitmap.h"
#include "utils.h"

static const int bitsperbyte=8;

/**
 * @brief “divide and round up” function
 * 
 * @param n 
 * @param d 
 * @return int 
 */
static int divup(int n, int d) {
  return (n+d-1)/d;
}

static int mapsize(unsigned int size, int e) {
  int blocksize=e2size(e);
  int blocks=divup(size,blocksize);
  int buddies=divup(blocks,2);
  return divup(buddies,bitsperbyte);
}

static int bitaddr(void *base, void *mem, int e) {
  int addr=buddyclr(base,mem,e)-base;
  int blocksize=e2size(e);
  return addr/blocksize/2;
}

extern BitMap bitmapnew(unsigned int size, int e) {
  int ms=mapsize(size,e);
  printf("%d\n",ms);
  BitMap block=mmalloc(ms);
  if ((long)block==-1)
    return 0;
  memset(block,0,ms); //memset() is used to fill a block of memory with a particular value
  return block;
}

extern void bitmapset(BitMap b, void *base, void *mem, int e) {
  int offset=bitaddr(base,mem,e);
  bitset(((unsigned char *)b)+offset/bitsperbyte,offset%bitsperbyte);
}

extern void bitmapclr(BitMap b, void *base, void *mem, int e) {
  int offset=bitaddr(base,mem,e);
  bitclr(((unsigned char *)b)+offset/bitsperbyte,offset%bitsperbyte);
}

extern int bitmaptst(BitMap b, void *base, void *mem, int e) {
  int offset=bitaddr(base,mem,e);
  return bittst(((unsigned char *)b)+offset/bitsperbyte,offset%bitsperbyte);
}

extern void bitmapprint(BitMap b, unsigned int size, int e) {
  int ms=mapsize(size,e);
  int byte;
  for (byte=ms-1; byte>=0; byte--)
    printf("%02x%s",((unsigned char *)b)[byte],(byte ? " " : "\n"));
}


// int main()
// {

//     BitMap b = bitmapnew(128, 2);

//     bitmapprint(b, 128, 2);

//     // Balloc new = bnew(4096,4,12);

//     // printf("%d\n", (int)new);
 
//     return 0;
// }