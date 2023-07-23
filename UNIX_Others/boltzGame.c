#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
	int n = 10; // the number of processes
	int pipes[11][2]; // the pipes
	int boltzNumber = 1;
	for(int i = 1; i <= n; i++)
	{
		pipe(pipes[i]);
		int cp = fork(); // child proccess
		if(cp == -1)
			exit(1);
		if(i == 1){
			close(pipes[1][0]); // close the unnecesarry pipes as soon as possible
			write(pipes[1][1], &boltzNumber, sizeof(int));
			close(pipes[1][1]);
		}
		else{
			read(pipes[i-1][0], &boltzNumber, sizeof(int));
			close(pipes[i-1][0]);
			boltzNumber++;
			if(boltzNumber % 7 == 0){
				int stopChance = rand() % 3;
			
			}
			write(pipes[i][1], &boltzNumber, sizeof(int));
			close(pipes[i][1]);
		}
		int dump = 0;
		waitpid(cp, &dump);
	}
	
	
	return 0; 
}



