#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
    int n;
    printf("n = ");
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
	int f = fork();
	if(f == -1){
	    perror("Error creating new process");
	}
	if(f == 0){
	    printf("C - Child ID = %d, Parent ID = %d\n", getpid(), getppid());
	}
	else
	    printf("P - Child ID = %d, Parent ID = %d\n", f, getpid());
    }
    for(int i = 0; i < n; i++)
	wait(0);
    return 0;
}
