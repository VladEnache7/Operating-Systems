#include <pthread.h>
#include <stdio.h>

#define n 100

pthread_mutex_t mutex;

int count = 0;

void* increment(){
	for(int i = 0; i < 10000; i++){
		pthread_mutex_lock(&mutex);
		count++;
		pthread_mutex_unlock(&mutex);
	}
}


int main(){
	// declaring the threads variables
	pthread_t t[n];
	
	// initializing the mutex
	pthread_mutex_init(&mutex, NULL);

	for(int i = 0; i < n; i++){
		pthread_create(&t[i], NULL, &increment, NULL);
		printf("T%d - created\n", i);
	}
	
	
	for(int i = 0; i < n; i++){
		pthread_join(t[i], NULL);
		printf("T%d - joined\n", i);
	}	
	
	printf("Count = %d\n", count);

	pthread_mutex_destroy(&mutex);

}
