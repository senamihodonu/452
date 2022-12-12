#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"


#include "freelist.h"

// typedef struct free_area_struct {
//     struct list_head free_list;
//     unsigned long *map;
// } free_area_t;

#define MAX_ORDER       10

typedef struct freelist_node{
    struct freelist_node* next;
    struct freelist_node* prev;
}Freelist_node;

typedef struct freelist{
    int upper;
    struct freelist_node levels[MAX_ORDER];
    int size; //total size
    int depth; //number of useable levels
    int lower;
} FreeList_h;


extern FreeList freelistnew(unsigned int size, int l, int u){
    FreeList_h* freelist = mmalloc(sizeof(FreeList_h));
    freelist->upper = u;
    freelist->size = size;
    freelist->depth = size2e(size)-l;
    freelist->lower = l;
    Freelist_node* head = mmalloc(sizeof(Freelist_node));
    freelist->levels[freelist->depth].next = head;
    head->prev = &(freelist->levels[freelist->depth]); //returns the address at the depth
    return freelist;
}

extern void *freelistalloc(FreeList f, void *base, int e, int l){
    FreeList_h* freelist = (FreeList_h*)f;
    if(e2size(e) > freelist->size){
        perror("space not available"), exit (EXIT_FAILURE);
    }
    int e_in_pool = e-l; //confirms that the given e is allowable in pool
                         //ie e = 4; if l = 1 then e_in_pool is actually
                         //4-1 = 3
    if(freelist->levels[e_in_pool].next != NULL){ 
        Freelist_node* free_node = freelist->levels[e].next;
        Freelist_node* set_next = free_node->next;
        Freelist_node* set_prev = free_node->prev;
        set_prev->next = set_next;
        set_next->prev = set_prev;
        free_node->next = NULL;
        free_node->prev = NULL;
        return free_node;      
    }

    int e_cpy = e_in_pool;
    while(freelist->levels[e_cpy].next == NULL) { //search for available node (i.e splitting)
        e_cpy++; //go up
    }

    while(e_cpy >= e_in_pool){

    }
}
extern void freelistfree(FreeList f, void *base, void *mem, int e, int l);
extern int freelistsize(FreeList f, void *base, void *mem, int l, int u);

extern void freelistprint(FreeList f, unsigned int size, int l, int u);