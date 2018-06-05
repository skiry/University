#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	
	int p[2],p2[2];

	if( pipe(p) < 0 ){
		perror("Pipe error");
		exit(1);
	}
		if( pipe(p2) < 0 ){
		perror("Pipe2 error");
		exit(5);
	}
	
	
	int f = fork();
	if( f < 0 ){
		perror("Fork error");
		exit(2);
	}
	else if( f == 0 ){ //fiu
		close( p[1] );//inchidem scriere p
		close( p2[0] );
		int x;
		dup2(p[1], STDOUT_FILENO );
		int nr;
		while(( x = read( p[0], nr, 4) ) > 0 )  {
				printf("%d", nr * 2);
				}
		close(p[0]);
		close(p2[1]);
	}
	else{ //parinte
		close( p[0] );//inchidem citire p
		int x,nr;
		dup2( p[1], STDOUT_FILENO ); //,1
		close( p[1] );
		for(int i = 0; i < 9; i++)
			printf("%d", i);
		dup2( 1, 1);
		while(( x = read( p2[0], nr, 4)) > 0){
			printf("Am primit: %d\n", nr);
		wait( 0 );
	}
		
	return 0;
}

