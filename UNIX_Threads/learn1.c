#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int v[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

void* thread_print(void* arg){
	int value = *(int*)arg;
	printf("-> %d\n", value);
}


int main(){
	pthread_t t[10];

	for(int i = 0; i < 10; i++){
		pthread_create(&t[i], NULL, &thread_print, v + i);
	}

	for(int i = 0; i < 10; i++){
		pthread_join(t[i], NULL);
	}


	return 0;
}

