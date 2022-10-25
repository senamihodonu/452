#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


#include "thread.h"
#include "error.h"
/**
 * @brief implementation thread handling module
 * @author senami hodonu
 */

/**
 * @brief allocates space for thread
 * 
 * @param n 
 * @return Thread 
 */
 extern Thread make_thread(int n) {
    Pt t = (Pt)malloc(sizeof(*t));
    if (!t) ERROR("malloc() failed");
    t->size = n;
    t->pt = (pthread_t*)malloc(sizeof(pthread_t) * n*sizeof(int*));
    return t;
 }

/**
 * @brief create a thread object
 * 
 * @param t 
 * @param routine 
 * @param args 
 * @param numofthreads 
 */
extern void create_thread(Pt t, Data routine, Data args, int numofthreads){
    t->size=numofthreads;
    for (int i=0; i<numofthreads; i++){
        pthread_create(&t->pt[i],0,(void*)routine,(void*)args);
    } 
}
/**
 * @brief function to wait for n number of threads
 * 
 * @param t 
 * @param numofthreads 
 */
extern void joining(Pt t, int numofthreads){
    t->size=numofthreads;
    for (int i=0; i<numofthreads; i++){
        pthread_join(t->pt[i],0);
    }
    free(t->pt);
}
