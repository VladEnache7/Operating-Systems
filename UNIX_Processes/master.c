#include <signal.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>

int main(int argc, char* argv[]){
	//signal(SIGCHLD, SIG_IGN); // ending the child process as soon as it finished - but the parent can end before the child\
	
	char argChild[200];
	for(int i = 1; i <= argc; i++){\
		int id = fork();
		if(id == 0) {// if is the child
			strcpy(argChild, argv[i]); // copy the name of the file
			strcat(argChild, ".CAPIT"); // add the .CAPIT
			
			execl("./cap", "./cap", argv[i], argChild, NULL); // execute the capitalization program

		} else { 
			printf("Parinte: %d ..> %s %s\n", id, argv[i], argChild);
		}
	}
	for (int i = 1; i <= argc; i++)
		wait(NULL);
	
	return 0;
}
