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
	
	for(int i = 1; i < argc; i++){
		strcat(str, argv[i]);
		printf("%s\n", str);
	}
	//TODO: put '\0' at the end of str
	printf("Final string ~%s~\n", str);
		

	// open the fifo for writing
	int writeFD = open("/tmp/fifo", O_WRONLY);
	if(writeFD == -1){
		perror("A - Error - open fifo flenor writing: ");
		exit(-1);
	}
	
	// writing the length of the string
	int len = strlen(str);
	int ret = write(writeFD, &len, sizeof(int));
	if(ret == -1){
		perror("A - Error - writing to fifo: ");
		exit(-1);
	}
	printf("A - wrote len %d\n", len);

	ret = write(writeFD, str, len * sizeof(char));
	if(ret == -1){
		perror("A - Error - writing to fifo: ");
		exit(-1);
	}
	printf("A - wrote str %s\n", str);

	close(writeFD); printf("A - closed fifo for writing\n");

	
	
	return 0;
}
