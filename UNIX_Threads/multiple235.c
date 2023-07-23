#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define nrThreads 10

// the variables
int v2, v3, v5;
// the mutexes for the variables
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m5 = PTHREAD_MUTEX_INITIALIZER;

int numbers = 0;
pthread_mutex_t nLock = PTHREAD_MUTEX_INITIALIZER;

void* thread(void* arg){
	int index = (int) arg; // trick to not deal with malloc
	printf("T%d - created\n", index);
	while(1){
		pthread_mutex_lock(&nLock);
		if(numbers == 30){
			printf("T%d - exiting\n", index);
			pthread_mutex_unlock(&nLock);
			break;
		}
		else{
			int randomNr = rand() % 30;
			numbers++;
			pthread_mutex_unlock(&nLock);
			
			printf("T%d - generated %d\n", index, randomNr);
			if(randomNr % 2 == 0){
				pthread_mutex_lock(&m2);
				v2++;
				pthread_mutex_unlock(&m2);
			}
			if(randomNr % 3 == 0){
				pthread_mutex_lock(&m3);
				v3++;
				pthread_mutex_unlock(&m3);
			}
			if(randomNr % 5 == 0){
				pthread_mutex_lock(&m5);
				v5++;
				pthread_mutex_unlock(&m5);
			}
		
		}
		//sleep(1);
	}

}

int main(){
	pthread_t t[nrThreads];

	srand(time(NULL));
		
	for(int i = 0; i < nrThreads; i++){
		pthread_create(&t[i], NULL, thread, i);
	}
	printf(" - Parent finished generating threads\n");
	
	for(int i = 0; i < nrThreads; i++){
		pthread_join(t[i], NULL);
	}
	printf(" - Parent finished joining threads\n");
	
	printf("--> v2 = %d, v3 = %d, v5 = %d <--\n", v2, v3, v5);
	return 0;
}
