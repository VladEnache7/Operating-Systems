#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
void f(int n){
	if(n > 0 || fork() == 0){
		printf("n = %d, PID: %d\n", n, getpid());
		f(n-1);
		exit(0);
	}
	wait(0);
}


int main(){
	
	f(3);
	
	return 0;
}
