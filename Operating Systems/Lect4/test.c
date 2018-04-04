#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(){

  int pid;
  printf("Parent: %d\n",getpid());
  pid = fork();

  if(pid == 0) { //child
  printf("Child: %d %d\n", getpid(), getppid());
  exit(0);
  }
  sleep(10);
//  wait(0);
  printf("Parent again: %d\n",getpid());
  return 0;
}
