#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t cons[3], prod[2];

pthread_rwlock_t rwl;

int global = 0;

void* rutina1(void *a){
	int x = *(int*)a;
	free(a);
	for( int i = 0; i < 20; ++i ){
		pthread_rwlock_rdlock( &rwl );
		printf("Consumer %i says global has the value %d\n", x, global);
		pthread_rwlock_unlock( &rwl );
		sleep(3);
	}
}

void* rutina2(void *a){
	int x = *(int*)a;
	free(a);
	int rnd;
	for( int i = 0; i < 60; ++i ){
		pthread_rwlock_wrlock( &rwl );
		rnd = rand() % 11 + 10;
		printf("Changed global from %d", global);
		global += rnd;
		printf(" to %d\n", global);
		pthread_rwlock_unlock( &rwl );
		sleep(1);
	}
}
int main(){

	srand(getpid());
	pthread_rwlock_init( &rwl, NULL );
	for(int e = 0; e < 3; e++){
		int* p = malloc( sizeof( int ) );
	*p = e + 1;
	if( pthread_create( cons + e, NULL, rutina1, p ) < 0 ){
		perror("Error creating the consumer's thread");
		exit(1);
	}
	}
	for( int e = 0; e < 2; e++){
	int* p1 = malloc( sizeof( int ) );
	*p1 = e + 1;
	if( pthread_create( prod + e, NULL, rutina2, p1 ) < 0 ){
		perror("Error creating the producer's thread");
		exit(2);
	}
	}
for(int e = 0; e<3;e++)
	pthread_join( cons[e], NULL );
for(int e = 0; e<2;e++)
	pthread_join(prod[e], NULL );
	
	printf( "Final result: %d\n", global );

	pthread_rwlock_destroy( &rwl );
	return 0;
}

