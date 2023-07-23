#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	
	fork();
	printf("Fork 1\n");
	wait(0);
	fork();
	printf("Fork 2\n");
	wait(0);
	fork();
 	printf("Fork 3\n");
	return 0;
}
