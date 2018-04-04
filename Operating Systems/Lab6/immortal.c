#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void rutina(int s){
	printf("Not today\n");
}

void rutina2(int s){
	printf("A murit\n");
}

int main(){

	signal(SIGINT, rutina);
	signal(SIGTERM, rutina);
	signal(SIGCHLD, rutina2);
	//while(1) sleep(1);
	int f = fork();
	if(f < 0){
		perror("Eroare la fork\n");
		exit(1);
	}
	else if(f == 0){
		printf("Child pid %d, parent pid: %d \n", getpid(), getppid());
		kill(getppid(), SIGINT);	
	}
	else{
		wait(0);
	}

	//printf("Child pid %d, parent pid: %d ", getpid(), getppid());
	return 0;
}
