#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
	int w2s[2]; // pipe who to sort
	
	pipe(w2s); // creating the pipe
	
	//the first child
	int id1 = fork();
	if(id1 == -1)
		return 1;
	
	if(id1 == 0){
		close(w2s[0]); // no need of reading for 1st child
		dup2(w2s[1], 1); // writing the output of stdout to pipe
		execlp("ls", "ls", NULL);
		printf("Error - execlp - ls\n");
		return 2; 
	}

	// second child
	int id2 = fork();
	if(id2 == -1)
		return 3;

	if(id2 == 0){
		close(w2s[1]); // no writing for 2nd child
		dup2(w2s[0], 0); // reading the input of stdin from pipe
		
		execlp("sort", "sort", NULL);
		printf("Error - execlp - sort\n");	
		return 4;	
	}
	
	// parent proccess
	close(w2s[0]); close(w2s[1]); // closing the pipe
	wait(0); wait(0); // waiting the 2 children
	return 0;	
}
