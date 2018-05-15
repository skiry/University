#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int fd = open("fifoWR", O_RDONLY);
	int x, cnt;
	while( (cnt = read( fd, &x, sizeof(int) ) > 0  ) ){
		printf("Received %d\n", x);
	}		

	close(fd);
	return 0;
}

