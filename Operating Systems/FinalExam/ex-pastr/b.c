#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
int n;
int *vect;

pthread_t* pd;
sem_t sem;
pthread_barrier_t barr;

void *fct( void* a){
int nr = *(int*)a;
for(int i = 0; i < n; ++i){
	sem_wait(&sem);
	printf("Thread %d changed from position %d to value %d\n",pthread_self(),nr,vect[nr]+1);
	vect[nr] += 1;
	sem_post(&sem);
}
pthread_barrier_wait(&barr);
printf("Done, id: %d\n", pthread_self());
return NULL;
}
int main(){

	int fif = open("transm.fifo", O_RDONLY);
	if( fif < 0 ){
		perror("Error opening fifo in b");
		exit(0);
	}
	read(fif, &n, sizeof(int));
	close(fif);
	vect = malloc(n*sizeof(int));
	for( int i = 0; i < n; ++i )
		vect[i] = i + 1;
	pd = malloc(n*sizeof(pthread_t));
	sem_init(&sem, 0, 1);
	pthread_barrier_init(&barr, NULL, n);
	for(int i = 0; i < n; ++i){
		int *p = malloc(sizeof(int));
			*p = i;
		pthread_create(pd + i, NULL, fct, p);
	}
	for(int i = 0; i < n; ++i)
		pthread_join(pd[1], NULL);
	sem_destroy(&sem);
	pthread_barrier_destroy(&barr);
	free(vect);
	free(pd);
	unlink("transm.fifo");
	return 0;
}
