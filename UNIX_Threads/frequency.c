#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int f[10];
pthread_mutex_t m[10]; // a mutex for every digit in the frequency vector

void* thread(void* arg){
	int x = (int) arg;
	int cx = x; // copy of x
	printf("T %d - started\n", x);

	while(cx > 0){
		int digit = cx % 10;
		pthread_mutex_lock(&m[digit]);
		f[digit]++;
		pthread_mutex_unlock(&m[digit]);
		cx /= 10;
	}

	printf("T %d - ended\n", x);
	return NULL;
}

int main(int argc, char** argv){
	// creating argc number of threads
	pthread_t* t = (pthread_t*)malloc(argc * sizeof(pthread_t));	
	
	// initializing the mutexes
	for(int i = 0; i < 9; i++)
		pthread_mutex_init(&m[i], NULL);
	
	// creating the threads
	for(int i = 1; i < argc; i++){
		int n = atoi(argv[i]);
		pthread_create(&t[i], NULL, &thread, n);
	}
	
	// joining the threads
	for(int i = 1; i < argc; i++){
		pthread_join(t[i], NULL);
	}
	
	// destroying the mutexes
	for(int i = 0; i < 9; i++)
		pthread_mutex_destroy(&m[i]);
	
	for(int i = 0; i <= 9; i++)
		printf("f[%d] = %d\n", i, f[i]);
	
	free(t);
	return 0;
}
