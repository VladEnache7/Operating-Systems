#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
	
	fork();
	if(fork()){
		fork();
	}
	printf("Salut\n");
	return 0;
}
