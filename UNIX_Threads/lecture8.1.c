#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> // rand
#include <unistd.h> // sleep
#include <time.h> 

void* thread(void* arg){
	printf("T%ld - started\n", pthread_self() % 1000);
	sleep(rand() % 5);
	printf("T%ld - ended\n", pthread_self() % 1000);
	return NULL;
}

int main(){
	pthread_t t[10];
	
	srand(time(NULL));

	// creating the threads
	for(int i = 0; i < 10; i++){
		pthread_create(&t[i], NULL, &thread, NULL);
	}
	
	// joining the threads
	for(int i = 0; i < 10; i++){
		pthread_join(t[i], NULL);
	}
	

	return 0;
}
