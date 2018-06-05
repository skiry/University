#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void f(int sig){
	if(sig == SIGINT){
		printf("No way\n");
	}
	else if(sig == SIGSTOP){
		printf("Nice try\n");
	}
}

int main() {
	signal(SIGINT, f);
	signal(SIGSTOP, f);
//	while(1);
int 	p = fork();
	printf("%d",p);
	return 0;
}
