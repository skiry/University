#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE* f = popen( "/bin/ls", "r" );

	if( f != NULL ){
		char* buffer = malloc( sizeof(char) * 37 );
		int x;

		while(( x = fread( buffer, 1, 36, f )) > 0 ){
			buffer[x] = 0;
			printf("Am primit: \n %s \n", buffer);
		}
		free( buffer );	
	}	
	pclose(f);
	return 0;
}
