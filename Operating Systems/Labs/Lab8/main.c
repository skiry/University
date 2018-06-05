#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	
	int p[2];

	if( pipe(p) < 0 ){
		perror("Pipe error");
		exit(1);
	}
	
	int f = fork();
	if( f < 0 ){
		perror("Fork error");
		exit(2);
	}
	else if( f == 0 ){ //fiu
		close( p[0] );
		dup2( p[1], STDOUT_FILENO );
		close( p[1] );
		if( execl("/bin/ls", "ls", NULL) < 0 ){
			perror("Execl error");
			exit(3);
		}
	}
	else{ //parinte
		close( p[1] );
		int x;
		char* buffer = malloc( sizeof(char) * 37 );

		while(( x = read( p[0], buffer, 36 )) > 0 ){
			buffer[x] = 0;
			printf("Am primit: \n %s \n", buffer);
			}
		wait( 0 );
		free( buffer );
		close( p[0] );
	}
		
	return 0;
}
