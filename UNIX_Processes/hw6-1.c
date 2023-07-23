#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv){
	if(argc != 3) {
    	printf("Usage: %s filename string\n", argv[0]);
		return 1;
  	}
	
	char *filename = argv[1];
	char *string = argv[2];
	
	FILE *d = fopen(filename, "w");
	if(d == NULL){
		printf("Error opening the file\n");
		return 1;
	}
	
	int len = strlen(string);
	for(int i = len - 1; i >= 0; i--){
		fputc(string[i], d);
	}

	fclose(d);
	return 0;
}
