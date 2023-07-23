#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	char word[50];
	while(1){
		memset(word, 0, 50);
		int len;
		
		// -- reading from program A -- //
		
		// opening fifo for reading
		int readFD = open("/tmp/uppercase", O_RDONLY);
		if(readFD == -1){
			perror("B - Error - open fifo for reading: ");
			exit(2);
		}
		printf("B - opened fifo for reading\n");

		// reading the length
		int returned = read(readFD, &len, sizeof(int));
		if(returned == -1){
			perror("B - Error - reading len: ");
			exit(2);
		}
		printf("B - read len %d\n", len);

		// reading the word from proccess B
		returned = read(readFD, word, sizeof(char)*len);
		if(returned == -1){
			perror("B - Error - reading word: ");
			exit(2);
		}
		printf("B - read word ~%s~\n", word);
		
		
		// -- writing to program B -- //		

		// opening the fifo for writing
		int writeFD = open("/tmp/uppercase", O_WRONLY);
		if(writeFD == -1){
			perror("B - Error - open fifo writing:");
			exit(1);
		}
		printf("B - opened fifo for writing\n");
		
		if(strcmp(word, "000") == 0){ // if is the end signal
			len = 0; // writing 0 for A
			int returned = write(writeFD, &len, sizeof(int));
			if(returned == -1){
				perror("B - Error - write len: ");
				exit(2);
			}
			printf("B - wrote len %d\n", len);
			close(writeFD); printf("B - closed fifo for writing\n");
			return 0;
		}
		
		// modifying the word
		for(int i = 0; word[i]; i++){
			if(word[i] >= 'a' && word[i] <= 'z')
				word[i] -= 32;	
		}
		printf("B - modified in ~%s~\n", word);

		// first writing the length of the word
		returned = write(writeFD, &len, sizeof(int));
		if(returned == -1){
			perror("B - Error - write len: ");
			exit(2);
		}
		printf("B - wrote len %d\n", len);

		// then writing the word
		returned = write(writeFD, word, sizeof(char)*len);
		if(returned == -1){
			perror("B - Error - write word: ");
			exit(2);
		}
		printf("B - wrote word ~%s~\n", word);

		close(writeFD);
		printf("B - closed fifo for writing\n");
	}	


	return 0;
}
