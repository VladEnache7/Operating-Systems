//pt fiecare cuvant face 2 procese, a si b. procesu a primeste cuvantu, face sir de frecventa pe literele lui. trimite sirul atat la procesul parinte, cat si la procesul b. procesul parinte afiseaza frecventele. procesu b face suma valorilor din sir si o afiseaza (practic lungimea cuv)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define n 20

int main(int argc, char** argv){
	int p2a[n][2], a2b[n][2], a2p[n][2];
	int pid[n][2];
	int len;
	
	for (int i = 1; i < argc; i++){
		pipe(p2a[i]);
		pipe(a2b[i]);
		pipe(a2p[i]);
	}
	printf("Pipes created\n");

	for(int i = 1; i < argc; i++){
		
		// creating the child
		pid[i][0] = fork();
		if(pid[i][0] == -1){
			perror("Error fork");
			exit(-1);
		}
		
		if(pid[i][0] == 0){ // child A code
			
			for(int j = 1; j < argc; j++){
				if(i != j){
					close(p2a[j][0]); close(p2a[j][1]);
					close(a2b[j][0]); close(a2b[j][1]);
					close(a2p[j][0]); close(a2p[j][1]);
				} else {
					close(p2a[j][1]); close(a2b[j][0]); close(a2p[j][0]);
				}
			}
			printf("A - C%d closed unneccessary pipes\n", i);
			
			// -- reading -- //

			// child i reading word i
		
			// reading the len
			read(p2a[i][0], &len, sizeof(int));
			printf("A - C%d read from P len %d\n", i, len);
			
			// reading string
			char str[50] = {0};
			read(p2a[i][0], str, sizeof(char) * len);
			printf("A - C%d read from P str ~%s~\n", i, str);
			
			// -- computing -- // 
			int f[32] = {0};
			for(int j = 0; j < len; j++){
				f[str[j] - 'a']++;
			}
			
			// -- sending to P -- // 
			
			write(a2p[i][1], f, sizeof(int) * 32);
			printf("A - wrote freq to P\n");

			// -- sending to B -- // 
			
			write(a2b[i][1], f, sizeof(int) * 32);
			printf("A - wrote freq to P\n");
			
			close(p2a[i][0]); close(a2b[i][1]); close(a2p[i][1]);
			printf("A - C%d close used pipes\n", i);
			exit(0);
		
		} else { 
			pid[i][1] = fork();
			if(pid[i][1] == -1){
				perror("B - Error fork");
				exit(-1);
			}
			if(pid[i][1] == 0){  // child B
				for(int j = 1; j < argc; j++){
					if(i != j){
						close(p2a[j][0]); close(p2a[j][1]);
						close(a2b[j][0]); close(a2b[j][1]);
						close(a2p[j][0]); close(a2p[j][1]);
					} else {
						close(p2a[j][1]);	close(p2a[j][0]);
					 	 
						close(a2p[j][0]);	close(a2p[j][1]);

						close(a2b[j][1]);
					}
				}
				printf("B - C%d closed unneccessary pipes\n", i);
				
				// -- reading freq from a -- //
				int f[32] = {0};
				
				read(a2b[i][0], f, sizeof(int) * 32);
				printf("B%d - read freq\n", i);

				int sum = 0;	
				for(int j = 0; j < 32; j++)
					sum += f[j];		
				
				printf("B%d - final sum is %d\n", i, sum);

				close(a2b[i][0]);
				printf("B%d - closed used pipes\n", i);
				exit(0);
			} else { // parent code
				close(p2a[i][0]);
				close(a2b[i][0]); close(a2b[i][1]);
				close(a2p[i][1]);
	
				// -- sending word -- //
				// parent sending word i
		
				// writing the len
				len = strlen(argv[i]);
				write(p2a[i][1], &len, sizeof(int));
				printf("P wrote to C%d len %d\n", i, len);

				// writing string
				write(p2a[i][1], argv[i], sizeof(char) * len);
				printf("P wrote to C%d str ~%s~\n", i, argv[i]);
				
				// -- reading freq from A -- //
				
				int f[32] = {0};
				read(a2p[i][0], f, sizeof(int) * 32); 
				printf("P - read freq \n");			
	
				for(int j = 0; j < 32; j++)
					if (f[j])
						printf("%c %d\n", (char)(j + 'a'), f[j]);
				
				close(p2a[i][1]); close(a2p[i][0]);
			}
		}
	}
	for(int i = 1; i < argc; ++i)
	{
		int pid = wait(NULL);
		int pid2 = wait(NULL);	
		printf("P waited %d\n", pid);
		printf("P waited %d\n", pid2);
	}



	return 0;
}
