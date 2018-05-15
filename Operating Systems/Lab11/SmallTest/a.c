#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int global = 0;

pthread_t a, b;
pthread_mutex_t var = PTHREAD_MUTEX_INITIALIZER;
void* f( void* v ){
	int e = *(int*)v;
	free(v);
	int x;
	for( int i = 0; i < 10; ++i){
		pthread_mutex_lock( &var );
		x = rand() % 11 + 10;
		global += x;
		printf("Added %d...Total %d\n", x, global);
		pthread_mutex_unlock( &var );
	}
}

void* f1( void* v ){
	int e = *(int*)v;
	free(v);
	int x;
	for( int i = 0; i < 10; ++i){
		pthread_mutex_lock( &var );
		x = rand() % 11 + 10;
		global -= x;
		printf("Subtracted %d...Total %d\n", x, global);
		pthread_mutex_unlock( &var );
	}
}

int main(){

	//a adds
	//b decrements
	
	//10 rand numbers bet 10 - 20;
	
	int* val = malloc(sizeof(int));
	*val = global;
	if( pthread_create( &a, NULL, f, val ) < 0 ){
		perror("Error creating thread");
		exit(1);
	}
	int* val2 = malloc(sizeof(int));
	*val2 = global;
	if( pthread_create( &b, NULL, f1, val2 ) < 0 ){
		perror("Error creating thread 2");
		exit(2);
	}

	pthread_join( a, NULL);
	pthread_join( b, NULL);

	pthread_mutex_destroy( &var);
	return 0;
}
