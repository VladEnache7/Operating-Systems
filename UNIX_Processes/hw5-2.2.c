#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


int main(){
	int arr[30];
	int n;	
	
	// getting the numbers from the user
	printf("Enter the number of integers: ");
  	scanf("%d", &n);

  	printf("Enter %d integers: ", n);
  	for(int i = 0; i < n; i++) {
    	scanf("%d", &arr[i]);
  	}


	int pid = fork();
	if (pid == 0){ // child process
		char *vec[32];  // vector of arguments to pass to execvp()
    	char str[16];

    	// convert integer arguments to strings
    	vec[0] = "./hw5-1";
    	sprintf(str, "%d", arr[0]); // printing in string s the number arr[0]
    	vec[1] = strdup(str); 	// duplicating str but allocating space dynamically
    	int j = 1;
		for(j = 1; j < n; j++) {
    	  	sprintf(str, "%d", arr[j]);
      		vec[j+1] = strdup(str);
    	}
    	vec[j+1] = NULL; // NULL at the end

		execvp("./hw5-1", vec);

		printf("Some Error occured\n");
	}
	else{
		int status;
		wait(&status);
		if(WEXITSTATUS(status) == 0)
			printf("Equal!!");
		else if(WEXITSTATUS(status) == 1)
			printf("Not Equal!!");
		else
			printf("The exit code is different from 0 and 1 so an aerror occurred");
	}
	
	return 0;
}
