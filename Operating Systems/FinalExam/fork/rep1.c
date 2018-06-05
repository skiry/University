#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//a program that creates 2 procceses F
//				     S1 
//				     S11
//such that S11 sends to S1 n numbers read from the keyboard, S1 multiplies them succesively with 1,2,3,...,n and sends them to F, F printing them to the screen
int main(){
	int n;

	int fs1[2], s11[2];
	if( pipe(fs1) < 0 ){
		perror("Error creating pipe fs1");
		exit(1);
	}
	if( pipe(s11) < 0 ){
		perror("Error creating pipe s11");
		exit(2);
	}

	int p = fork();
	if( p < 0 ){
		perror("Error making fork 1!");
		exit(3);
	}
	if( p == 0 ){
		close( fs1[1] );
		int son = fork();
		if( son < 0 ){
			perror("Error making fork 2!");
			exit(4);
		}
		if( son == 0 ){ //S11
			close( s11[0] );
			printf("Give n: ");
			scanf("%d", &n);
			printf("\n %d Numbers: ", n);
			for( int i = 0; i < n; ++i ){
				//
			}
			close( s11[1] );
		}
		close( fs1[0] );
	}
	return 0;
}
