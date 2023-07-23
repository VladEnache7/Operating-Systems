#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	int status = system("$?");
	printf("%d\n", status);
	int result = WEXITSTATUS(status);
	printf("%d\n", result);	
	return 0;
}
