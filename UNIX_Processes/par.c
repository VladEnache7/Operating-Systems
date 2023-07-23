#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){

	int n1, n2, odds = 0, evens = 0, nonNumbs = 0;
	// macking a process for every pereche of numbers
	for(int i = 1; i < argc; i++){
		if(fork() == 0){
			n1 = atoi(argv[i]); // return 0 if not a number
			n2 = atoi(argv[i + 1]);
			if (n1 == 0 || n2 == 0) // if one of them is not a number
				exit(2); 	
			exit((n1 + n2) % 2); // else exit with their sum
		} 		
	}
	// in the parent get the exit codes from the childs
	for(int i = 1; i < argc; i++){
		int exitCode = 3;
		wait(&exitCode);
		printf("ExitCode? : %d\n", exitCode);
		printf("ExitCode??? : %d\n", WEXITSTATUS(exitCode));
		switch(WEXITSTATUS(exitCode)){
			case 0: { evens++; break; }
			case 1: { odds++;	break; }
			default: nonNumbs++;
		}
	}
	printf("Even pairs: %d, Odd pairs: %d, Not numbers: %d\n", evens, odds, nonNumbs);
	return 0;
}
