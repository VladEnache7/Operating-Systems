#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#include <time.h> // for srand()

#define n 6

int main(){
	char r[n][20]; // fifos for right sending

	int pid[n]; // the ids of all the proccesses
	
	srand(time(NULL)); // making the rand real random
	
	// creating the fifos
	for(int i = 0; i < n; i++){
		sprintf(r[i], "/tmp/fifo%d", i);
		if (mkfifo(r[i], 0666) == -1){
			printf("Error first mkfifo - maybe %s already exits\n", r[i]);
			if( unlink(r[i]) == 0) {
				printf("Unlinking successfully\n");
				if( mkfifo(r[i], 0666) == -1){
					printf("Error second fifo - exiting\n");
					exit(2);
				}
				else
					printf("Second mkfifo - success\n");
			}
		}
		
		printf("Fifos %s created\n", r[i]);
	}
		
	
	int start = rand() % n; 

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
				printf("C%d starts\n", i);
				char c = 'A';
				char dir = '1'; // first the direction is 1
				int writeFD = open(r[(i + 1) % n], O_WRONLY);
				//printf("C%d - opened %s for writing\n", i, r[(i + 1) % n]);
				
				// writing the direction
				write(writeFD, &dir, sizeof(char));
				printf("C%d wrote direction %c\n", i, dir);
				
				// writing the character
				write(writeFD, &c, sizeof(c));
				printf("C%d wrote %c\n", i, c);

				close(writeFD);
			//	printf("C%d - closed %s for writing\n", i, r[(i + 1) % n]);
				

				start = -1; // making start unreachable

			}
			while(1){
				char c = '-';
				char dir = '-';
				int readFD = open(r[i], O_RDONLY); // read file descriptor
				printf("C%d - opened %s for reading\n", i, r[i]);
				
				// reading the direction
				if(read(readFD, &dir, sizeof(c)) == 0 || dir == '-'){
					printf("C%d read nothing - break while\n", i);
					break;
				}
				printf("C%d read direction %c\n", i, dir);
				
				// reading the character
				if(read(readFD, &c, sizeof(c)) == 0 || c == '-'){
					printf("C%d read nothing - break while\n", i);
					break;
				}
				printf("C%d read %c\n", i, c);
				close(readFD); printf("C%d - closed %s for reading\n", i, r[i]);
						
				c++; // next letter
		
				if(rand() % 100 < 40 && !(c - '0' > 1 && c - '0' < 10) && c != 'Z') { // and c is not a number (end of execution)
					c++; // mistake another next letter
					dir = (dir == '1') ? '0' : '1';
					printf("\nA mistake was made by C%d => direction changes\n\n", i);
				}
				char writeTo[20];
				if (dir == '1')
					strcpy(writeTo,r[(i + 1) % n]);
				else
					strcpy(writeTo,r[(i - 1) + (i == 0) * n]);

				printf("C%d will write to %s\n", i, writeTo);

				if(c == 'Z'){
					printf("C%d reached Z - the game is finished\n", i);
					// sending a number for the next child in order to end waiting
					c = '1';
					int writeFD = open(writeTo, O_WRONLY); // write file descriptor
					printf("C%d - opened %s for writing\n", i, writeTo);

					// writing the direction	
					write(writeFD, &dir, sizeof(c));
					printf("C%d wrote the direction %c\n", i, dir);

					// writing the character		
					write(writeFD, &c, sizeof(c));
					printf("C%d wrote %c - in order to end execution for the other\n", i, c);
					close(writeFD); printf("C%d - closed %s for writing\n", i,writeTo);

					break;
				}
				if(c - '0' > 1 && c - '0' < 10){
					printf("C%d - got the end signal\n", i);
					if (c - '0' == n){
						printf("C%d - the last one to end\n", i);
						break;
					}
					int writeFD = open(writeTo, O_WRONLY); // write file descriptor
					printf("C%d - opened %s for writing\n", i, writeTo);	

					// writing the direction	
					write(writeFD, &dir, sizeof(c));
					printf("C%d wrote the direction %c\n", i, dir);						

					// writing the character
					write(writeFD, &c, sizeof(c));
					printf("C%d wrote %c - to end execution for the other\n", i, c);
					close(writeFD); printf("C%d - closed %s for writing\n", i, writeTo);

					break;
				}
				if ( c >= 'A' && c < 'Z'){		
					int writeFD = open(writeTo, O_WRONLY); // write file descriptor
					printf("C%d - opened %s for writing\n", i, writeTo);
				
					// writing the direction	
					write(writeFD, &dir, sizeof(c));
					printf("C%d wrote the direction %c\n", i, dir);						

					// writing the character	
					write(writeFD, &c, sizeof(c));
					printf("C%d wrote %c\n", i, c);
					close(writeFD); printf("C%d - closed %s for writing\n", i, writeTo);
				}
				else{
					printf("Somehow, C%d got outside of alphabet - exiting\n", i);
					exit(2);
				}
			}
			printf("C%d is exiting\n", i);
			exit(0);
		}


	}
	
	// waiting for the all children
	for(int i = 0; i < n; i++){
		int pid = wait(0);
		printf("P - waited for %d child\n", pid);
	}

	// delete all the fifos
	for(int i = 0; i < n; i++){
		unlink(r[i]);
	}	
	printf("All fifos was deleted\n");
	
	return 0;
}
