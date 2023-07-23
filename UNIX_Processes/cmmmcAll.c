#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
	int v[50] = {0};	
	int n;
	printf("Enter how many number you want to write:");
	scanf("%d", &n);
	
	// reading the numbers
	for(int i = 0; i < n; i++){
		printf("v[%d] = ", i);
		scanf("%d", &v[i]);
	}
	
	printf("P - read the numbers:\n");
	for(int i = 0; i < n; i++){
		printf("v[%d] = %d\n", i, v[i]);
	}


	int cmmmcAll;

	// for the first 2 numbers
	int pid = fork();

	if(pid == -1) { perror("cmmmcAll - Error - fork"); exit(-1);}
	
	if(pid == 0){
		char str1[20] = {0}, str2[20] = {0};
		sprintf(str1, "%d", v[0]);
		sprintf(str2, "%d", v[1]);		
		printf("C - execl with %s & %s\n", str1, str2);	
		execl("./cmmmc", "./cmmmc", str1, str2, "/tmp/cmmmc", NULL);
		printf("cmmmcAll - Error with execl\n");
		exit(-1);
	}
	else{
		int status;
		wait(&status);	
		cmmmcAll = WEXITSTATUS(status);
		printf("P - got %d\n", cmmmcAll);
	}

	// computing cmmmc with previous cmmmc and v[i]
	for(int i = 2; i < n; i++){
		int pid = fork();

		if(pid == -1) { perror("cmmmcAll - Error - fork"); exit(-1);}
	
		if(pid == 0){
			char str1[20] = {0}, str2[20] = {0};
			sprintf(str1, "%d", cmmmcAll);
			sprintf(str2, "%d", v[i]);	
			printf("C - execl with %s & %s\n", str1, str2);
			execl("./cmmmc", "./cmmmc", str1, str2, "/tmp/cmmmc", NULL);
			printf("cmmmcAll - Error with execl\n");
			exit(-1);	
		} else {
			int status;
			wait(&status);	
			cmmmcAll = WEXITSTATUS(status);
			printf("P - got %d\n", cmmmcAll);		

		}
	}

	printf("Cmmmc of all numbers is %d\n", cmmmcAll);
	
	return 0;
}
