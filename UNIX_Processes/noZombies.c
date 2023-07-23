#include <signal.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>


void waiter(){
	int cid = wait(0);	// end execution of the child process as he ended
	printf("waiter: %d\n", cid);
	signal(SIGCHLD, waiter);
}

int main(){
	
	for(int i = 0; i < 10; i++){
		int pid = fork();
		if(pid == 0){
			sleep(1);
			exit(0);
		}
	}
	for(int i = 0; i < 9; i++){
		int childID = wait(0);
		printf("Normal wait: %d\n", childID);
	}
	signal(SIGCHLD, waiter);
	printf("Parent ended");
	return 0;
}
