#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "utils.h"
#include "balloc.h"


extern void *mmalloc(size_t size){
    Balloc new = mmap(NULL, size, PROT_READ | PROT_WRITE, 
                        MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (new == MAP_FAILED) perror("mmap not allocated"), exit (EXIT_FAILURE);
    return new;
}

/**
 * @brief Given an integer e, function raises 
 * 
 * @param e 
 * @return unsigned int 
 */
extern unsigned int e2size(int e){
    int ans = 1;
    int a = 2;
    while (e > 0)
    {
        int last_bit = (e & 1);
        if(last_bit){
            ans = ans * a;
        }
        a = a * a;
        e = e >> 1;
    }
    return ans;
}

/**
 * @brief Given a size, returns a power of 2 
 * 
 * @param size 
 * @return int 
 */
extern int size2e(unsigned int size){
    return size == 1 ? 1 : 1 << (32-__builtin_clzl(size-1));
}



extern void bitset(unsigned char *p, int bit){
    *p = (unsigned char)((long int)p | (1 << (bit -1)));
}

extern void bitclr(unsigned char *p, int bit){
    *p = (unsigned char)((long int)p & (~(1 << (bit - 1))));
}

extern void bitinv(unsigned char *p, int bit){
    *p = (unsigned char)((long int)p ^ (1 << (bit - 1)));
} //bit invserse

extern int bittst(unsigned char *p, int bit){
    if((unsigned char)((long int)p | (1 << (bit -1)))){
        return 1;
    } 
    return 0;
}  //bit test if bit is 1 or 0

extern void *buddyset(void *base, void *mem, int e);
extern void *buddyclr(void *base, void *mem, int e){ return NULL;}
extern void *buddyinv(void *base, void *mem, int e);
extern int buddytst(void *base, void *mem, int e);
