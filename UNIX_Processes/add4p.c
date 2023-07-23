#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
//#include <sys/wait.h>

int main(){
	int a[] = {1, 2, 3, 10};
	int c2p[2]; // pipe children to parent
	
	if(pipe(c2p) == -1)	// creating the pipe
	{
		printf("Error - pipe\n");
		return 1;
	}		
	// child code
	int id = fork();
	if(id == -1)
	{
		printf("Error - fork\n");
		return 2;
	}	
	if(id == 0){
		close(c2p[0]); // in the child close reading
		a[2] += a[3];
		if(write(c2p[1], &a[2], sizeof(int)) == -1){ // write the resulf of addition
			printf("Error - write\n");
			return 3;
		}
		close(c2p[1]); // close writing for child
		exit(0); // making sure the child stops at this
	}
	else{
		close(c2p[1]); // close the writing for parent
		a[0] += a[1];
		wait(0);
		if(read(c2p[0], &a[2], sizeof(int)) == -1){
			printf("Error - write\n");
         	return 3;
		}
		
		close(c2p[0]); // close the reading for parent
		a[0] += a[2];
		printf("Sum is %d\n", a[0]);	
	}
	return 0;
}
