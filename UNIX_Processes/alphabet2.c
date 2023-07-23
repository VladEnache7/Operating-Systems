#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


#define n 2

int main(){
	int p[n+1][2];
	int pids[n];
	
	// opening the pipes
	for(int i = 0; i < n; i++)
		pipe(p[i]);
	
	// randomly choosing the player to start the game
	int start = rand() % n;
	int play = start;
	
	int pid1 = fork();
	if(pid1 == -1)
		printf("Error fork\n");
	if(pid1 == 0){
		while(1){
			if(start == 0){
				printf("P0 - starting with A\n");
				char c = 'A';
				write(p[1][1], &c, sizeof(char));
				printf("P0 - writing %c\n", c);
				start = -1;
			}
			else if(play == 0){
				char c;
				read(p[0][0], &c, sizeof(char));
				printf("P0 - read %c\n", c);
				c++;
				if(c == 'Z'){
					printf("P0 - Finished the alphabet\n");
					break;
				}
				write(p[1][1], &c, sizeof(char));
				printf("P0 - writing %c\n", c);
			}
			play = (play + 1) % n;
		}
		close(p[0][0]); close(p[0][1]); close(p[1][0]); close(p[1][1]);
		printf("P0 - Closed the pipes\n");
		exit(0); // exit at the end of the execution
	} else {
		int pid2 = fork();
		if(pid2 == 0){
			close(p[0][0]); close(p[1][1]); 
			while(1){
				if(start == 1){
					char c = 'A';
					write(p[0][1], &c, sizeof(char));
					printf("P1 - writing %c\n", c);
					start = -1;
				}
				else if(play == 1){
					char c;
					printf("P1 - waiting to read\n");
					read(p[1][0], &c, sizeof(char));
					printf("P1 - read %c\n", c);
					c++;
					if(c == 'Z'){
						printf("P1 - Finished the alphabet\n");
						break;
					}
					write(p[0][1], &c, sizeof(char));
					printf("P1 - writing %c\n", c);
				}
				play = (play + 1) % n;
			}
			close(p[0][1]); close(p[1][0]);
			printf("P1 - Closed the pipes\n");
			exit(0); // exit at the end of the execution
		}
	}
	close(p[0][0]); close(p[0][1]); close(p[1][0]); close(p[1][1]); // in the parent closing all the pipes
	printf("Parent - Closed the pipes\n");
	// waiting for all the child
	for(int i = 0; i < n; i++){
		int pid = wait(0);
		printf("Parent got %d child\n", pid);
	}

	return 0;
}
