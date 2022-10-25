#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

// typedef struct pt_struct
// {
//   int size;
//   pthread_t pt[];
// } *Pt;

typedef struct pt_struct
{
    /* data */
    int size;
    pthread_t* pt;
}*Pt;

typedef void *Thread;
typedef void *Data;

extern Thread make_thread(int n);
extern void create_thread(Pt t, Data routine, Data args, int numofthreads);
extern void joining(Pt t, int numofthreads);

#endif

