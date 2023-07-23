


int main(){
	long n = 0;
	char str[60] = {0}, *ptr;
	char *arr[60];
	int sizeArr = 0;
	printf("Reading number untill it reads something that is not a number\n");
	while(1){
		printf(">>>");
		scanf("%s", &str);
		n = strtol(str, &ptr, strlen(str) - 1);
		if(ptr == str || n == LONG_MAX || n == LONG_MIN)
			break;
		char *
	}
	int pid = fork();
	if (pid == 0){
		execl("./a.out", "./a.out", 5, 5, NULL);
		printf("Some Error occured\n");
	}
	else{
		int status;
		wait(&status);
	}
	
	return 0;
}
