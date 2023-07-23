#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){

	int p = 0;
	for(int i = 0; i < 3; i++)
		if(p == 0){
			printf("Child created\n");
			p = fork();
			
		}
		else{
			wait(0);
			printf("Child waited\n");
		}

	return 0;
}
