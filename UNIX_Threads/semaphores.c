#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define n 20

sem_t sem;

void* thread(void* arg){
	int index = (int) arg;
	printf("T%d - waiting\n", index);
	
	sem_wait(&sem);
	printf("T%d - Got in\n", index);
	sleep(rand() % 5 + 1);
	printf("T%d - Exited\n", index);
	sem_post(&sem);
	return NULL;
}


int main(){
	srand(time(NULL));
	pthread_t t[n];

	// initializing the semaphore with value of 4
	sem_init(&sem, 0, 4);
	
	// creating the threads
	for(int i = 0; i < n; i++){
		pthread_create(&t[i], NULL, &thread, i);
	}

	// joining the threads
	for(int i = 0; i < n; i++){
		pthread_join(t[i], NULL);
	}

	
	sem_destroy(&sem);
	return 0;
}
