#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int fd, n, x;
	if( ( fd = mkfifo( "f1", 0600 ) ) < 0 ){
		perror("Error making fifo\n");
		exit(1);
	}
	
	printf("N: ");
	scanf("%d", &n);

	printf("Trying to open fifo\n");

	int fifoD = open( "f1", O_WRONLY );
	if( fifoD < 0 ){
		perror("Error opening fifo\n");
		exit(2);
	}
	
	printf("Opened fifo\n");
	
	if( write( fifoD, &n, sizeof(int) ) < 0 ){
		perror("Error writing n\n");
		exit(3);
	}

	for( int i = 0; i < n; ++i ){
		x = rand() % 11 + 10;
		if( write( fifoD, &x, sizeof(int) ) < 0 ){
			perror("Error sending number\n");
			exit(4);
		}
	}
	close( fifoD );
	unlink( "f1" );

	return 0;
}
