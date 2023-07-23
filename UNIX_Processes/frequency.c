



int main(int argc, char** argv){
	int p2a[2], a2b[2], b2p[2];
	char str[100] = {0};
	
	int ret;	

	// opening the pipes
	ret = pipe(p2a); 
	if(ret == -1){
		perror("Error pipe");
		exit(-1);
	}
	pipe(a2b);
	if(ret == -1){
		perror("Error pipe");
		exit(-1);
	}
	pipe(b2p);
	if(ret == -1){
		perror("Error pipe");
		exit(-1);
	}	

	// the parent builds the string from argv
	for(int i = 1; i < argc; i++){
		strcat(str, argv[i]);
		printf("%s\n", str);		
	}
	printf("Final string ~%s~\n", str);
		
	// writing the length
	int len = strlen(str);
	ret = write(p2a[1], &len, sizeof(int));
	if(ret == -1){
		perror("Error writing p2a");
		exit(-1);
	}
	printf("P - wrote len %d", len);

	// writing the string
	ret = write(p2a[1], str, sizeof(char) * len);
	if(ret == -1){
		perror("Error writing p2a");
		exit(-1);
	}	
	printf("P - wrote str ~%s~", str);

	int pid	= fork(); // creating child A
	
	if(pid == -1){
		perror("Error - fork");
		exit(-1);
	}
	
	// child A code
	if(pid == 0){
		close(p2a[1]);
		close(a2b[0]);
		close(b2p[1]);
		close(b2p[0]);
		printf("A - close unnecessary pipes\n");
		
		
		// reading the len
		ret = read(p2a[0], &len, sizeof(int));
 		if(ret == -1){
			perror("Error reading p2a");
			exit(-1);
		}
		printf("A - read len %d\n", len);

		// reading the string
		ret = read(p2a[0], str, sizeof(char)*len);
 		if(ret == -1){
			perror("Error reading p2a");
			exit(-1);
		}
		printf("A - read str ~%s~n", len);

		
	
	} else {
		int pid2 = fork();
		if(pid2 == -1){
			perror("Error - fork");
			exit(-1);
		}

		// child B code
		if(pid2 == 0){
			

		} else { // parent code


		}
	}

	return 0;
}
