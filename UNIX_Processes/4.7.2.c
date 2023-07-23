#include <stdio.h>
#include <errno.h>
#include <string.h>

// verifing if in the current directory we have a given file

int main(){
	char s[200], fileName[] = "alphabetSkip.c";
	FILE* fd = popen("ls", "r");
	
	while(1){
		char* p = fgets(s, 200, fd);
		if(p == NULL)  // there is no more to read from ls
			break;
		if(strstr(s, fileName) != NULL){
			printf("Yess, we found the file %s in the current directory\n", fileName);
			return 0;
		}
		
	}
	printf("Noo, we have not find the file %s in the current directory\n", fileName);
	
	return 0;
}
