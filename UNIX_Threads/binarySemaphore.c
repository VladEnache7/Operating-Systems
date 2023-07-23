#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define THREAD_NUM 1

sem_t semFuel;

int* fuel;

void* thread(void* arg){
	*fuel += 50;
	printf("Increased to %d\n", *fuel);
	sem_post(&semFuel); // posting that it finished using fuel variable
	return NULL;
}


int main(){
	pthread_t t;
	
	sem_init(&semFuel, 0, 0);

	fuel = (int*) malloc(sizeof(int));	
	*fuel = 0;	
	printf("Initial value %d\n", *fuel);

	pthread_create(&t, NULL, &thread, NULL);

	// waiting until the thread finished using the allocated variable
	sem_wait(&semFuel);
 
	free(fuel); // then freeing the memory
	printf("Memory dealocated\n");

	pthread_join(t, NULL);
	
	sem_destroy(&semFuel);
	return 0;
}
