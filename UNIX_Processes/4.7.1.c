#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	FILE* fd = popen("sort", "w"); // fd - file descriptor
	if(fd == NULL){
		perror("Erorr popen: ");
		exit(2);
	}
	printf("-->Popen succeded\n");
		
	for(int i = 0; argv[i]; i++)
		fprintf(fd, "%s\n", argv[i]);

	pclose(fd);
	return 0;
}
