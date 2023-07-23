#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define THREAD_NUM 2

sem_t semFull;
sem_t semEmpty;

int buffer[10], count = 0;
pthread_mutex_t mutexBuffer = PTHREAD_MUTEX_INITIALIZER;


void* producer(void* arg){
	int index = (int) arg;
	while(1){
		// Producing
		int x = rand() % 100;
	
		// Trying to sell it
		sem_wait(&semEmpty); // wait to be demand

		pthread_mutex_lock(&mutexBuffer);

		buffer[count++] = x;
		printf("P%d - produced %d\n", index, x);

		pthread_mutex_unlock(&mutexBuffer);	

		sem_post(&semFull);	// post product available
	}
}


void* consumer(void* arg){
	int index = (int) arg;
	while(1){
		
		// Trying to buy some product
		sem_wait(&semFull); 	// wait to be products

		pthread_mutex_lock(&mutexBuffer);
		int x = buffer[--count];
		printf("C%d - bought %d\n", index, x);

		pthread_mutex_unlock(&mutexBuffer);	
		
		sem_post(&semEmpty);	// post demand available
		
		sleep(1);
	}

}


int main(){
	srand(time(NULL));
	pthread_t t[THREAD_NUM];
	
	// initializing the semaphores
	sem_init(&semFull, 0, 0); // there are no slots full
	sem_init(&semEmpty, 0, 10); // there are 10 empty slots at first

	// creating the threads
	for(int i = 0; i < THREAD_NUM; i++)
		if(i % 2 == 0)
			pthread_create(&t[i], NULL, &producer, i);
		else
			pthread_create(&t[i], NULL, &consumer, i);
	
	// joining the threads
	for(int i = 0; i < THREAD_NUM; i++)
		pthread_join(t[i], NULL);
	
	// destroying the semaphores
	sem_destroy(&semFull);
	sem_destroy(&semEmpty);
	return 0;
}
