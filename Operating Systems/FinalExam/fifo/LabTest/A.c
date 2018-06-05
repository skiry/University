#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int fd = open("fifoWR", O_WRONLY);
	int x;
	for( int i = 0; i < 10; ++i ){
		x = rand() % 500 + 1;
		write( fd, &x, sizeof(int));
		printf("Sent %d\n", x);
	}		

	close(fd);

	return 0;
}
