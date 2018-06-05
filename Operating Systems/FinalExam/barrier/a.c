#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
pthread_t* pd;
int n, done;
int nr;
pthread_barrier_t bar;
pthread_mutex_t mut;
void* fct(void* a){
	int id = *(int*)a;
	pthread_barrier_wait(&bar);
	while(id!=nr);
	pthread_mutex_lock(&mut);

	printf("My id:%d\n",id);
	if(done!=1){	
		printf("Read next thread id: ");
		scanf("%d",&nr);
		--done;
	}
	else printf("Last thread\n");
	pthread_mutex_unlock(&mut);
	return NULL;

}

int main() {
	
	
	scanf("%d",&n);
	pthread_barrier_init(&bar,NULL, n);
	pthread_mutex_init(&mut, NULL);

	pd = malloc( n * sizeof(pthread_t) );
	done = n;
	nr = 0;
	for(int i = 0; i < n; ++i ){
		int *p = malloc(sizeof(int));
		*p = i;
		pthread_create(pd + i, NULL, fct, p);
	}
	for(int i = 0; i < n; ++i )
		pthread_join(pd[i], NULL);
	pthread_barrier_destroy(&bar);
	pthread_mutex_destroy(&mut);
	return 0;

}

