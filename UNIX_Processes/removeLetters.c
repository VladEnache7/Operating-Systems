#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	int p2c[2], c2p[2]; // pipe parent to child 
	
	if(pipe(p2c) == -1 || pipe(c2p) == -1){ // creating the pipes
		printf("Error - creating one of the pipes\n");
		exit(2);
	}
	
	int pid = fork(); // creating the child
	
	if(pid == -1){
		printf("Error - fork\n");
		exit(3);
	}
	
	// <-- parent code -->
	if(pid != 0){
		close(p2c[0]); 	// parent is not reading from parent to child
		close(c2p[1]);	// parent is not writing to child to parent
		printf("P - closed unnecesarry pipes\n");
		
		char str[50];
		printf("Enter a string (>25 characters, no spaces & tabs): ");
		fgets(str, 50, stdin);

		//char str[50] = "AnaAreMereGalbeneSiRosiiSiVerzi"; // the string at the beginning 
		int len = strlen(str); 
		
		if(str[len - 1] == '\n'){
			str[len - 1] = '\0';
			len--;
		}		
	
		// firstly, parent sends the string to the child

		// writing the length of the string
		if(write(p2c[1], &len, sizeof(int)) < 0){
			printf("Error - P writing len\n");
			exit(2);
		}
		printf("P - wrote len %d\n", len);

		// writing the string
		if(write(p2c[1], str, sizeof(char) * len) < 0){
			printf("Error - P writing the string\n");
			exit(2);
		}
		printf("P - wrote -%s-\n", str);

		while(1){
			// --- reading ---		
	
			// reading the length from the child
			int nRead = read(c2p[0], &len, sizeof(int));

			if(nRead == -1){
				printf("P - Error reading\n");
				exit(2);
			}	
			if(nRead == 0){
				printf("P - read nothing - breaking while\n");
				break;
			}

			printf("P - read length %d\n", len);

			if(len < 3){
				printf("P - length read is less then 3 - breaking while\n");
				close(p2c[1]); close(c2p[0]); 
				printf("P - closed the used pipes\n");
				break;
			}	
			
			// before reading empty the string
			memset(str, 0, 50);


			// reading the string from the child
			nRead = read(c2p[0], str, sizeof(char)*len);

			if(nRead == -1){
				printf("P - Error reading\n");
				exit(2);
			}	
			if(nRead == 0){
				printf("P - read nothing - breaking while\n");
				break;
			}

			printf("P - read -%s-\n", str);
			
			// --- changing ---
			
			len -= 2; // decreasing the length by 2
			memmove(str, str + 1, len);
			str[len] = '\0';
			printf("P - changed str to -%s-\n", str);			

			// --- writing ---

			// writing the lenth of the string
			if(write(p2c[1], &len, sizeof(int)) == -1){
				printf("P - Error writing len\n");
				exit(2);
			}
			printf("P - wrote len %d\n", len);

			// writing the string
			if(write(p2c[1], str, sizeof(char) * len) == -1){
				printf("P - Error writing len\n");
				exit(2);
			}

			printf("P - wrote -%s-\n", str);
			
		}

	} else { // <-- child code -->
		printf("Child created succesfully\n");
		close(p2c[1]); 	// child is not reading from child to parent
		close(c2p[0]);	// child is not writing to parent to child
		printf("C - closed unnecesarry pipes\n");
		
		char str[50];
		int len;
		
		while(1){
			// --- reading ---
	
			// reading the length from the parent
			int nRead = read(p2c[0], &len, sizeof(int));

			if(nRead == -1){
				printf("P - Error reading\n");
				exit(2);
			}	
			if(nRead == 0){
				printf("P - read nothing - breaking while\n");
				break;
			}

			printf("C - read length %d\n", len);
			
			if(len < 3){
				printf("C - length read is less then 3 - exiting\n");
				close(c2p[1]); close(p2c[0]); 
				printf("C - closed the used pipes\n");
				exit(0);
			}			
			
			// before reading empty the string
			memset(str, 0, 50);

			// reading the string from the child
			nRead = read(p2c[0], str, sizeof(char)*len);

			if(nRead == -1){
				printf("P - Error reading\n");
				exit(2);
			}	
			if(nRead == 0){
				printf("P - read nothing - breaking while\n");
				break;
			}

			printf("C - read -%s-\n", str);
			
			// --- changing ---
			
			for(int i = 0; i < len; i++)
				if(strchr("AEIOUaeiou", str[i])){	// if str[i] is a vowel
					for(int j = i; j < len - 1; j++)	// remove it
						str[j] = str[j+1];
					len--;
					str[len] = '\0';
					break;	
				}
			printf("C - changed str to -%s-\n", str);	

			// --- writing ---

			// writing the lenth of the string
			if(write(c2p[1], &len, sizeof(int)) == -1){
				printf("P - Error writing len\n");
				exit(2);
			}
			printf("C - wrote len %d\n", len);

			// writing the string
			if(write(c2p[1], str, sizeof(char) * len) == -1){
				printf("P - Error writing len\n");
				exit(2);
			}
			printf("C - wrote -%s-\n", str);
			
		}		

	}
		

	return 0;
}
