#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	
	if (fork() || fork()){
		fork();
	}
	printf("PID:%d, Parent ID: %d\n", getpid(), getppid());	
	
	return 0;
}
