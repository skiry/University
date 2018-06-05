#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#DEFINE N 5
#DEFINE sp 5

int spaghetti = sp;

void* fct(void* a){
	int i = *(int*) a;
	printf("Filozoful %d a pornit\n", i);
	free(a);
	int dr = i; //the right hand side fork
	int st = ( i + 1 ) % N; //the left hand side fork
	
	do{
		if( pthread_mutex_trylock( bete[st] ) == 0 ){
			if( pthread_mutex_trylock( bete[dr] ) == 0 ){
				//mutex bol, mancam, uspeel(100), scadem din bol rand,daca nu, pthread mutex unlock
			}
		}

	}while();
}
int main(){

	pthread_t filozof[N];
	
	pthread_mutex_t bete[N];
	pthread_mutex_t bol = PTHREAD_MUTEX_INITIALIZER;

	for( int i = 0; i < N; ++i )
		pthread_mutex_init( &bete[i], NULL );//mutex initialization
	
	for( int i = 0; i < N; ++i){
		int* p = (int*) malloc ( sizeof(int) );
		*p = i;	
		if( pthread_create( &filozof[i], NULL, fct, p ) < 0 ){;//pthread creation
			perror( "Error creating thread" );
			exit(1);
		}
	}

	for( int i = 0; i < N; ++i )
		pthread_join( filozof[i], NULL );

	for( int i = 0; i < N; ++i )
		pthread_mutex_destroy( &bete[i] );
	pthread_mutex_destroy( &bol );

	return 0;
}
