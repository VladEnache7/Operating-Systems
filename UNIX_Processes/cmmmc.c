#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int cmmmc(int x, int y){
	int max = (x > y) ? x : y;
	while(!(max % x == 0 && max % y == 0))\
		max++; 
	return max;
}

int main(int argc, char** argv){
	if(argc != 4){
		printf("Invalid input - Syntax: %s number1 number2 filename", argv[0]);
		exit(1);
	}
	int x = atoi(argv[1]), y = atoi(argv[2]);
	if(x == 0 || y == 0){
		printf("argument 1 or 2 is not a number\n");
		exit(2);
	}
	int result = cmmmc(x, y);

	// write in the file
	int writeFD = open(argv[3], O_WRONLY);
	if(writeFD == -1){
		perror("cmmmc.c Error open file for writing");
		exit(-1);
	}
	
	// converting the result to string
	char strResult[20] = {0};
	sprintf(strResult, "%d", result);
	
	int returned = write(writeFD, strResult, sizeof(char) * strlen(strResult));
	if(returned == -1){
		perror("cmmmc.c Error writing to file");
		exit(-1);
	}

	exit(result); // also returned the result
}	
