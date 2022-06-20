#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

typedef enum {Think,Munch} State;
typedef struct {
  State state;
  sem_t *sticks[2];
} Phil;

enum {size=5};			// number of phils/sticks
static sem_t sticks[size];	// chopstick semaphores
static Phil phils[size];
static const int cycles=10;	// think/eat iterations per phil

static sem_t output;
static void print(int id, State state) {
  sem_wait(&output);
  phils[id].state=state;
  for (int i=0; i<size; i++)
    fprintf(stderr,"%c%c",
	    phils[i].state==Think ? '!' : 'O',
	    i<size-1 ? ' ' : '\n');
  sem_post(&output);
}

static void init() {
  sem_init(&output,0,1);
  for (int i=0; i<size; i++)
    sem_init(&sticks[i],0,1);
  for (int i=0; i<size; i++) {
    phils[i].state=Think;
    phils[i].sticks[0]=&sticks[i];          // [i?0:1]
    phils[i].sticks[1]=&sticks[(i+1)%size]; // [i?1:0]
  }
}

static void fini() {
  for (int i=0; i<size; i++)
    sem_destroy(&sticks[i]);
  sem_destroy(&output);
}

void *be(void *a) {
  int id=(int)(long)a;
  for (int i=cycles; i; i--) {
    sem_wait(phils[id].sticks[0]);
    sem_wait(phils[id].sticks[1]);
        print(id,Munch); sleep(1); print(id,Think);
    sem_post(phils[id].sticks[0]);
    sem_post(phils[id].sticks[1]);
  }
  return 0;
}

int main() {
  init();
  pthread_t tids[size];
  for (int i=0; i<size; i++)
    pthread_create(&tids[i],0,be,(void *)(long)i);
  for (int i=0; i<size; i++)
    pthread_join(tids[i],0);
  fini();
  return 0;
}
