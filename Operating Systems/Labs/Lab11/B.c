#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int fd, n, x;
	
	printf("Trying to open fifo\n");

	int fifoD = open( "f1", O_RDONLY );
	if( fifoD < 0 ){
		perror("Error opening fifo\n");
		exit(1);
	}
	
	printf("Opened fifo\n");
	
	if( read( fifoD, &n, sizeof(int) ) < 0 ){
		perror("Error reading n\n");
		exit(2);
	}

	for( int i = 0; i < n; ++i ){
		if( read( fifoD, &x, sizeof(int) ) < 0 ){
			perror("Error reading number\n");
			exit(3);
		}
		printf( "Got %d\n", x );
	}
	close( fifoD );

	return 0;
}
