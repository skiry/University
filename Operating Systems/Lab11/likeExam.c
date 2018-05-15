//thr de pe poz imp - voc, pare - cons

//thread pt fiecare
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int g;
void* f( void* a ){
	char e[100];
	int v, c;
	strcpy(e, *(char*)a);
	free(a);
	for( int i = 0; i < strlen(e); ++i)
		if( strchr( "aeiou", e ) == 0 )
			v++;
		else c++;
}

int main(int argc, char* argv[]){

	pthread_t tr[argc];

	for( int i = 0; i < argc; ++i ){
		int* p = malloc( sizeof( char ) * srtlen(argv[i]) );
		strcpy(p, argv[i]);
		if( pthread_create( tr + i, NULL, f, p ) < 0 ){
			perror("Error creating thread");
			exit(1);
		}
	}

	for( int i = 0; i< argc; ++i )
		pthread_join( tr[i], NULL );

	pthread_mutex_destroy( &m );
	return 0;
}
