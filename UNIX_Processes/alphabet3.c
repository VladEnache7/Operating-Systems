#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include <time.h> // for srand()

#define n 6

int main(){
	int p[n][2]; // the pipes for all the proccesses
	int pid[n]; // the ids of all the proccesses
	
	srand(time(NULL)); // making the rand() really random
	
	// opening the pipes
	for(int i = 0; i < n; i++)
		pipe(p[i]);
	
	int start = rand() % n; // momently starting with C0

	// creating the children
	for(int i = 0; i < n; i++){
		pid[i] = fork();
		if(pid[i] == -1) {
			printf("Error - Fork\n"); 
			exit(2);
		}
		if(pid[i] == 0){
			
			// first closing the unnecessary pipes
			for(int j = 0; j < n; j++)
				if(j != i)
					close(p[j][0]), close(p[(j+1)%n][1]);
			printf("C%d closed the unnecessary pipes\n", i);

			if(start == i){
				char c = 'A';
				write(p[(i + 1)%n][1], &c, sizeof(c));
				printf("C%d wrote %c\n", i, c);
				start = -1;
			}
			while(1){
					char c = '-';
					if(read(p[i][0], &c, sizeof(c)) == 0){
						printf("C%d read nothing - break while\n", i);
						break;
					}
					printf("C%d read %c\n", i, c);	
					c++;
					if(c == 'Z'){
						printf("C%d reached Z - the game is finished\n", i);
						break;
					}
					write(p[(i + 1)%n][1], &c, sizeof(c));
					printf("C%d wrote %c\n", i, c);
			}
			// closing the pipes the child used
			close(p[i][0]); close(p[(i + 1) % n][1]);
			printf("C%d closed the pipes and is exiting\n", i);
			exit(0);
		}


	}
	// parent closing all the pipes because does not use them
	for(int i = 0; i < n; i++){
		close(p[i][0]); close(p[i][1]);
	}
	printf("Parent closed all his pipes\n");

	// waiting for the all children
	for(int i = 0; i < n; i++){
		int pid = wait(0);
		printf("Parent waited for %d child\n", pid);
	}
		
	
	return 0;
}
