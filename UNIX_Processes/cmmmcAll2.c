#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

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

	// -- for the first 2 numbers --

	char str1[20] = {0}, str2[20] = {0};
	sprintf(str1, "%d", v[0]);
	sprintf(str2, "%d", v[1]);		
	
	// building the call for system	
	char call[100] = {0};
	strcat(call, "./cmmmc ");
	strcat(call, str1);
	strcat(call, " ");
	strcat(call, str2);
	strcat(call, " ");
	strcat(call, "/tmp/cmmmc");

	printf("call = ~%s~\n", call);		

	int status = system(call);

	cmmmcAll = WEXITSTATUS(status);
	

	// computing cmmmc with previous cmmmc and v[i]
	for(int i = 2; i < n; i++){
		char str1[20] = {0}, str2[20] = {0};
		sprintf(str1, "%d", cmmmcAll);
		sprintf(str2, "%d", v[i]);		
	
		// building the call for system	
		memset(call, 0, 100); // reseting the call
		strcat(call, "./cmmmc ");
		strcat(call, str1);
		strcat(call, " ");
		strcat(call, str2);
		strcat(call, " ");
		strcat(call, "/tmp/cmmmc");

		printf("call = ~%s~\n", call);		

		int status = system(call);

		cmmmcAll = WEXITSTATUS(status);		
		printf("cmmmcAll = %d\n", cmmmcAll);
	}

	printf("Cmmmc of all numbers is %d\n", cmmmcAll);
	
	return 0;
}
