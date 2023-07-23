#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
	for (int i = 0; i < 3; i++){
		int pid = fork();
		if(pid == 0){ // then this is the child
			printf("Child - PID = %d, PPID = %d\n", getpid(), getppid());
			exit(0); // needed to stop the child process
		}
		else{
			printf("Parent - PID = %d, PPID = %d\n", getpid(), getppid());
		}
	}
	
	// waiting for all the children
	for(int i = 0; i < 8; i++)
		wait(0);


	return 0;
}
