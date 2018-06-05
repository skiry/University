#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t a, b;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int global = 0;

void* rutina(void *a){
	int x = *(int*)a;
	free(a);
	int rnd;
	for( int i = 0; i < 10; ++i ){
		pthread_mutex_lock( &m );
		rnd = rand() % 11 + 10;
		printf("Thread %d modified %d in", x + 2, global);
		global += rnd * x;
		printf(" %d->%d\n", global, rnd);
		pthread_mutex_unlock( &m );
		usleep(200);
	}
}

int main(){

	int* p = malloc( sizeof( int ) );
	*p = 1;
	srand(getpid());
	if( pthread_create( &a, NULL, rutina, p ) < 0 ){
		perror("Error creating the first thread");
		exit(1);
	}
	int* p1 = malloc( sizeof( int ) );
	*p1 = -1;
	if( pthread_create( &b, NULL, rutina, p1 ) < 0 ){
		perror("Error creating the second thread");
		exit(2);
	}

	pthread_join( a, NULL );
	pthread_join( b, NULL );
	
	printf( "Final result: %d\n", global );

	pthread_mutex_destroy( &m );
	return 0;
}
