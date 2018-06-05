#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	
	int pf[2], fp[2];
	//parinte-fiu, fiu-parinte
	//
	if( pipe(pf) < 0 ){
		perror("Pipe parent-child error");
		exit(1);
	}

	if( pipe(fp) < 0 ){
		perror("Pipe child-parent error");
		exit(5);
	}

	int f = fork();
	if( f < 0 ){
		perror("Fork error");
		exit(2);
	}
	else if( f == 0 ){ //fiu
		close( pf[1] );
		close( fp[0] );
		int n, nr;
		//cand trimitem un sir de elemente printr un canal de comunicare, o data trimitem lungimea sirului si apoi sirul

		if( read( pf[0], &n, sizeof(int) ) < 0 ){
			perror("Error reading n");
			exit(6);
		}
		printf("N: %d\n", n);

		for( int i = 0; i < n; ++i ){
			if( read( pf[0], &nr, sizeof(int) ) < 0 ){
				perror("Error reading a number");
				exit(7);
			}
			nr *= 2;
			if( write( fp[1], &nr, sizeof(int) ) < 0 ){
				perror("Error sending a number");
				exit(8);
			}
		}
		close( pf[0] );
		close( fp[1] );
		exit(0);
	}
	else{ //parinte
		close( pf[0] );
		close( fp[1] );
		int n, nr;
		printf("Dati n:");
		scanf( "%d", &n );

		if( write( pf[1], &n, sizeof(int) ) < 0 ){
			perror("Error sending n from the parent");
			exit(9);
		}
		printf("AM trimis:%d\n",n);
		for( int i = 0; i < n; ++i ){
		nr = rand()%11 + 10;
			if( write( pf[1], &nr, sizeof(int) ) < 0 ){
			perror("Error sending a number from the parent");
			exit(10);
			}
		}

		for( int i = 0; i < n; ++i ){
			if( read( fp[0], &nr, sizeof(int) ) < 0 ){
			perror("Error reading a number from the child");
			exit(11);
			}
			printf( "Am primit: %d\n", nr );
		}
		wait(0);
		close( fp[0] );
		close( pf[1] );
	}
		
	return 0;
}

