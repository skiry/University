#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int fd = open("fifoRD", O_RDONLY);
	int fd1 = open("fifoWR", O_WRONLY);
	int x, cnt;
	while( (cnt = read( fd, &x, sizeof(int) ) > 0  ) ){
		x *= 2;
		write( fd1, &x, sizeof(int) );
	}		

	close(fd);
	close(fd1);
	return 0;
}

