#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
int main() {
	
	int p[2];
	if( pipe(p) < 0 ){
		perror("Error making pipe");
		exit(0);
	}

	int n;
	int f = fork();
	if( f < 0 ){
		perror("Error making fork");
		exit(1);
	}
	if( f == 0 ){//child
		close(p[0]);
		printf("Give n: ");
		scanf("%d", &n);
		write(p[1], &n, sizeof(int));
		close(p[1]);
	}
	else{//parent
		close(p[1]);
		if( mkfifo("transm.fifo", 0700) < 0 ){
			perror("Error creating fifo");
			exit(3);
			}
		int fif = open("transm.fifo", O_WRONLY);
		if( fif < 0 ){
			perror("Error opening fifo");
			exit(4);
		}
		read(p[0], &n, sizeof(int));
		write(fif, &n, sizeof(int));
		close(p[0]);
		close(fif);
	}
	wait(0);
	


	return 0;

}

