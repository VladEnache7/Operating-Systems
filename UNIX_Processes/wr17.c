#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
	int p[2];
	pipe(p);

	if(fork() == 0){
		sleep(1);
		//dup2(0, p[0]);
		execl("bin/sort", "/bin/sort", NULL);	
		printf("Execl error\n");
		exit(0);
	}
	write(p[1], "random", 7);
	
	
	return 0;
}
