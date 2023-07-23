#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	//execlp("ls", "ls", "-l", NULL);
	system("ls -l *.c");
	return 0;
}
