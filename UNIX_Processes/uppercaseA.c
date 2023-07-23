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
	printf("Enter strings after >>> and I'll give them in uppercase\nTo end the program write '000'\n");
	while(1){
		memset(word, 0, 50);
		printf(">>>");
		scanf("%s", word);
		printf("A - from keyboard ~%s~\n", word);
		
		int len = strlen(word);

		// -- writing to program B -- //		

		// opening the fifo for writing
		int writeFD = open("/tmp/uppercase", O_WRONLY);
		if(writeFD == -1){
			perror("A - Error - open fifo writing:");
			exit(1);
		}
		printf("A - opened fifo for writing\n");
		
		// first writing the length of the word
		int returned = write(writeFD, &len, sizeof(int));
		if(returned == -1){
			perror("A - Error - write len: ");
			exit(2);
		}
		printf("A - wrote len %d\n", len);

		// then writing the word
		returned = write(writeFD, word, sizeof(char)*len);
		if(returned == -1){
			perror("A - Error - write word: ");
			exit(2);
		}
		printf("A - wrote word ~%s~\n", word);

		close(writeFD);
		printf("A - closed fifo for writing\n");

		// -- reading from program B -- //
		
		// opening fifo for reading
		int readFD = open("/tmp/uppercase", O_RDONLY);
		if(readFD == -1){
			perror("A - Error - open fifo for reading: ");
			exit(2);
		}
		printf("A - opened fifo for reading\n");

		// reading the length
		returned = read(readFD, &len, sizeof(int));
		if(returned == -1){
			perror("A - Error - reading len: ");
			exit(2);
		}
		printf("A - read len %d\n", len);
		
		if(len == 0){ // exit semnal
			printf("A got 0 - exiting\n");
			close(readFD); printf("A - closed reading from fifo\n");
			return 0;
		}

		// reading the word from proccess B
		returned = read(readFD, word, sizeof(char)*len);
		if(returned == -1){
			perror("A - Error - reading word: ");
			exit(2);
		}
		printf("A - read word ~%s~\n", word);

		printf("<---- %s ---->\n", word);// for the user
	}	


	return 0;
}
