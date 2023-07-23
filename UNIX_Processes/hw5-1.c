#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

//compares 2 or more numbers as arguments and returns 0 if all are equal, 1 otherwise

int main(int argc, char *argv[]){
	int n = atoi(argv[1]);

	if(n == 0) // the first argument was not a number
	{
		//printf("Exiting with 2\n");
		exit(2);
	}
	int allEqual = 0;
	
	for(int i = 2; i < argc; i++){
		int x = atoi(argv[i]);
		if(n == 0) // the argument was not a number
		{
			//printf("Exiting with 2\n");
         	exit(2);	
		}
		if(x != n)
			allEqual = 1;
	}
	//printf("Exiting with %d\n", allEqual);
	exit(allEqual);
}
