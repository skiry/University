#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
pthread_t pd[200];
pthread_mutex_t mut;
int G = 0;
void* fct(void* a){
	char* c = (char*)a;
int  i;	if( mkfifo("myfifo",0700) < 0 ){	
			perror("Error making fifo");
			exit(3);
		}
int f = fork();
	if( f < 0 ){
		perror("Error making fork!");
		exit(2);
	}
	int lettNo = 0;
	if( f == 0 ){ //process A, child
		for(int i = 0; i < strlen(c); ++i)
			if(c[i]>='a'&&c[i]<='z'){
				c[i] = toupper(c[i]);
				++lettNo;	//	printf("%c",c[i]);
			}
			else if(c[i]>='A'&&c[i]<='Z') ++lettNo;
		printf("New word: %s and has %d letters\n",c, lettNo);
		pthread_mutex_lock(&mut);
		G += lettNo;
		printf("Proccess id %d changed G from %d to %d\n", pthread_self(), G-lettNo, G);
		pthread_mutex_unlock(&mut);			
		int wrt = open("myfifo", O_WRONLY);
		if( wrt < 0 ){
			perror("Error ar opening fifo");
			exit(5);
		}
		int len = strlen(c);
		write(wrt, &len, sizeof(int));
		write(wrt, c, sizeof(char)*strlen(c));
		close(wrt);
		exit(0);
	}
	//parent proccess
	//wait(0);
	pthread_mutex_lock(&mut);
	int rdd = open("myfifo", O_RDONLY);
	if( rdd < 0 ){
		perror("Error at opening fifo");
		exit(4);
	}

	char* new;
	int mylen;
	read(rdd, &mylen, sizeof(int));
	read(rdd, new, sizeof(char)*mylen);
	printf("From fifo: %s si nr %d\n", new, mylen);
	close(rdd);
		pthread_mutex_unlock(&mut);			
	wait(0);
	unlink("myfifo");	
	return NULL;
}

int main() {
	
	int i=0;	
		
	pthread_mutex_init(&mut, NULL);
	char cuv[100];
	do{
	scanf("%s",&cuv);
	char* c = (char*)malloc(100*sizeof(char));
	c = cuv;
	if( pthread_create(pd+i,NULL, fct, c) < 0){
		perror("Error creating threads");
		exit(1);
	}
	++i;  
	}while(strcmp(cuv,"stop"));
	int j = 0;
	for(j = 0; j < i; ++j )
	pthread_join(pd[j],NULL);
//	unlink("myfifo");
	pthread_mutex_destroy(&mut);
	return 0;
}

