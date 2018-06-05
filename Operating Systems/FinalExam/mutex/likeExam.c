//thr de pe poz imp - voc, pare - cons
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//thread pt fiecare
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
struct arg{
int cnt;
char* str;
};

int g = 0;
void* f( void* a ){
	struct arg p = *(struct arg*)a;
	free(a);
	for( int i = 0; i < strlen(p.str); ++i)
	 {pthread_mutex_lock(&m);
	if(p.cnt % 2){
	   
		if( strchr( "aeiou", p.str[i] ) == 0 )
			g++;}
			else {
			if( strchr( "aeiou", p.str[i] ) != 0 )
		 g++;
		}
		pthread_mutex_unlock(&m);}
}

int main(int argc, char* argv[]){

	pthread_t* tr = malloc(sizeof(pthread_t)*argc);

	for( int i = 0; i < argc-1; ++i ){
		struct arg* p = (struct arg*)malloc(sizeof(struct arg));
		p->cnt = i + 1;
		p->str = argv[i+1];
		if( pthread_create( tr + i, NULL, f, p ) < 0 ){
			perror("Error creating thread");
			exit(1);
		}
	}

	for( int i = 0; i< argc; ++i )
		pthread_join( tr[i], NULL );

	pthread_mutex_destroy( &m );
	printf("Rezultat: %d", g);
	return 0;
}
