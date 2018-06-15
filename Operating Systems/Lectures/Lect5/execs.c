#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	printf("Before\n");
	if(fork() == 0){
	execlp("echo", "echo", "here", NULL);
	exit(0);
	}
	printf("After\n");
	wait(0);
	return 0;
}
