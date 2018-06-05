#include <stdio.h>
#include <pthread.h>

#define V 1000
#define B 10

int seats = 100;
float price = 100;

pthread_mutex_t mtx;

void* viewer(void* p) {
  int k = (int)p;
  pthread_mutex_lock(&mtx);
  printf("V%d: Seats %d, price %f\n",
         k, seats, price*(2.0f-seats/100.0f));
  pthread_mutex_unlock(&mtx);
  return NULL;
}

void* buyer(void* p) {
  int k = (int)p;
  pthread_mutex_lock(&mtx);
  printf("B%d: My seat is %d, price %f\n",
         k, seats, price*(2.0f-seats/100.0f));
  seats--;
  pthread_mutex_unlock(&mtx);
  return NULL;
}

int main() {
  pthread_t tv[V], tb[B];
  int i;

  pthread_mutex_init(&mtx, NULL);
  for(i=0; i<V; i++) {
    pthread_create(&tv[i], NULL, viewer, (void*)i);
  }
  for(i=0; i<B; i++) {
    pthread_create(&tb[i], NULL, buyer, (void*)i);
  }

  for(i=0; i<V; i++) {
    pthread_join(tv[i], NULL);
  }
  for(i=0; i<B; i++) {
    pthread_join(tb[i], NULL);
  }
  pthread_mutex_destroy(&mtx);
  return 0;
}

