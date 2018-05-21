#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int n, g;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t b;
void* f(void* a){
	int el;
	for( int i = 0; i < n; ++i ){
		el = rand() % 5 + 1;
		pthread_mutex_lock( &m );
		g += el;

		pthread_mutex_unlock( &m );
		usleep( 100 );
	}
//`	pthread_barrier_wait( &b );
	printf("Value: %d\n", g);
			
}

int main(){
	srand(getpid());
	printf("Give n: ");
	scanf("%d", &n);
	pthread_barrier_init( &b, NULL, n );
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
	pthread_barrier_destroy( & b );
	pthread_mutex_destroy( &m );
	return 0;
}
