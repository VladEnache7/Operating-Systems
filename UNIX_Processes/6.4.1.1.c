#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char** argv) {

	signal(SIGCHLD, SIG_IGN); // this should kill the child as soon as he is done
 	int pid;
	pid = fork();
	if(pid == 0) {
 		sleep(10); exit(0);
 	}
 	sleep(15); wait(0); sleep(5);
 	return 0;
}
