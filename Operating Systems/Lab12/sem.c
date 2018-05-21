#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "semaphore.h"

int n, g;
sem_t s;
void* f(void* a){
	int el;
	sem_wait( &s );
	g++;
	printf( "G:%d\n", g );
	g--;
	sem_post( &s );
}

int main(){
	srand(getpid());
	printf("Give n: ");
	scanf("%d", &n);
	sem_init( &s, 0, 2 );
		//    1 daca e sa mosteneasca cand facem cu fork
	pthread_t* t = (pthread_t*) malloc (n * sizeof(pthread_t));
	for( int i = 0; i < n; ++i ){
		if( pthread_create( t + i, NULL, f, NULL ) < 0 ){
			perror("Error creating thread");
			exit(1);
		}
	}

	for( int i = 0; i < n; ++i )
		pthread_join( t[i], NULL );	

	free( t );
	sem_destroy( & s );
	return 0;
}

