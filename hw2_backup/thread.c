#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


#include "thread.h"
#include "error.h"


 extern Thread make_thread(int n) {
    // Pt t = (Pt)malloc(sizeof(*t)+n*sizeof(char*));
    Pt t = (Pt)malloc(sizeof(*t));
    if (!t) ERROR("malloc() failed");
    t->size = n;
    t->pt = (pthread_t*)malloc(sizeof(pthread_t) * n*sizeof(char*));
    // for (int i=0; i<n; i++) t->pt[i] = 0;
    return t;
 }

extern void create_thread(Pt t, Data routine, Data args, int numofthreads){
    t->size=numofthreads;
    for (int i=0; i<numofthreads; i++){
        int p = pthread_create(&t->pt[i],0,(void*)routine,(void*)args);
        printf("create %d\n", p);
    } 
}
extern void joining(Pt t, int numofthreads){
    t->size=numofthreads;
    for (int i=0; i<numofthreads; i++){
        pthread_join(t->pt[i],0);
        printf("join\n");
    } 
}

extern void thread_freedom(Pt t){
    // for (int i=0; i<t->size; i++) free(t->pt[i]);
    free(t->pt);
}