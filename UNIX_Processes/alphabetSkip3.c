#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <time.h> // for srand()

#define n 6

int main(){
	char r[n][20]; // fifos for right sending
	char l[n][20]; // fifos for left sending

	int pid[n]; // the ids of all the proccesses
	
	int right = 1; // the direction (1 = A->Z, 0 = Z->A)

	int end = 0; // = 1 -> the sign is the end of the game

	srand(time(NULL)); // making the rand real random
	
	// creating the fifos
	for(int i = 0; i < n; i++){
		sprintf(r[i], "/tmp/fifoRight%d", i);
		sprintf(l[i], "/tmp/fifoLeft%d", i);
		if (mkfifo(r[i], 0666) == -1 && unlink(r[i]) == -1 && mkfifo(r[i], 0666) == -1){ // making the right sending fifo (if the fifos already exits it delete them & create again
			printf("Error - mkfifo\n");
			exit(2);
		}
		if (mkfifo(l[i], 0666) == -1 && unlink(l[i]) == -1 && mkfifo(l[i], 0666) == -1){ // making the left sending fifo
			printf("Error - mkfifo\n");
			exit(2);
		}
		printf("Fifos %s & %s created\n", r[i], l[i]);
	}
		
	
	int start = 0 % n; // momently starting with C0
	int play = start;

	// creating the children
	for(int i = 0; i < n; i++){
		// creating the child
		pid[i] = fork(); 
		
		// checking for Fork Error
		if(pid[i] == -1) {
			printf("Error - Fork\n"); 
			exit(2);
		}
		
		

		// child code
		if(pid[i] == 0){
			printf("C%d - created\n", i);
			// code for the child who start
			if(start == i){
				char c = 'A';
				int writeFD = open(r[(i + 1) % n], O_WRONLY);
				printf("C%d - opened %s for writing\n", i, r[(i + 1) % n]);
				write(writeFD, &c, sizeof(c));
				printf("C%d wrote %c\n", i, c);
				close(writeFD);
				printf("C%d - closed %s for writing\n", i, r[(i + 1) % n]);
				

				start = -1; // making start unreachable

				play = (play + 1) % n; // going to the next proccess
				printf("play = %d", play);
			}
			while(1){
				if (end == 1){
						printf("C%d got end signal\n", i);
						break;
					}
				if(play == i){
					
					char c = '-';
					int readFD = open(r[i], O_RDONLY); // read file descriptor
					printf("C%d - opened %s for reading\n", i, r[i]);
					if(read(readFD, &c, sizeof(c)) == 0 || c == '-'){
						printf("C%d read nothing - break while\n", i);
						break;
					}
					close(readFD); printf("C%d - closed %s for reading\n", i, r[i]);
					printf("C%d read %c\n", i, c);	
					c++;
					if(c == 'Z'){
						printf("C%d reached Z - the game is finished\n", i);
						play = (play + 1) % n;
						end = 1; printf("end = 1\n");
						break;
					}
					int writeFD = open(r[(i + 1) % n], O_WRONLY); // write file descriptor
					printf("C%d - opened %s for writing\n", i, r[(i + 1) % n]);	
					write(writeFD, &c, sizeof(c));
					printf("C%d wrote %c\n", i, c);
					close(writeFD); printf("C%d - closed %s for writing\n", i, r[(i + 1) % n]);
					play = (play + 1) % n; // going to the next proccess
					printf("play = %d", play);
				}
					
			}
			printf("C%d is exiting\n", i);
			exit(0);
		}


	}
	
	// waiting for the all children
	for(int i = 0; i < n; i++){
		int pid = wait(0);
		printf("Parent waited for %d child\n", pid);
	}

	// delete all the fifos
	for(int i = 0; i < n; i++){
		unlink(r[i]);
		unlink(l[i]);
	}	
	printf("All fifos was deleted\n");
	
	return 0;
}
