#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char** argv){
	char str[100] = {0};
	
	// open the fifo for reading
	int readFD = open("/tmp/fifo", O_RDONLY);
	if(readFD == -1){
		perror("B - Error - open fifo for reading: ");
		exit(-1);
	}
	
	// reading the length of the string
	int len; 
	int ret = read(readFD, &len, sizeof(int));
	if(ret == -1){
		perror("A - Error - reading to fifo: ");
		exit(-1);
	}
	printf("A - read len %d\n", len);

	ret = read(readFD, str, len * sizeof(char));
	if(ret == -1){
		perror("A - Error - reading to fifo: ");
		exit(-1);
	}
	printf("A - read str %s\n", str);

	close(readFD); printf("A - closed fifo for reading\n");

	
	
	return 0;
}
