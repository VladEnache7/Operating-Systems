#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define threads 20

int relativePrimes = 0;
pthread_mutex_t r = PTHREAD_MUTEX_INITIALIZER;

typedef struct pair{
	int first;
	int second;
}pair;


void* thread(void* arg){
	pair* n = (pair*) arg;
	
	printf("T %d & %d - started\n", n->first, n->second);
	
	for(int d = 2; d <= n->first; d++){
		if(n->first % d == 0 && n->second % d == 0){
			printf("T %d & %d - NO\n", n->first, n->second);
			free(n);
			return NULL; // simply exit from the program
}
	}
	// if there is no common divizor grater then 1 
	pthread_mutex_lock(&r);
	relativePrimes++;
	pthread_mutex_unlock(&r);

	printf("T %d & %d - YES\n", n->first, n->second);
	free(n);

	return NULL;
}

int main(int argc, char** argv){
	pthread_t t[threads];

	for(int i = 1; i < argc - 1; i++){
		pair* n = (pair*) malloc(sizeof(pair));
		n->first = atoi(argv[i]);
		n->second = atoi(argv[i+1]);
		pthread_create(&t[i], NULL, &thread, n);
	}
	


	for(int i = 1; i < argc - 1; i++){
		pthread_join(t[i], NULL);
	}
	
	printf("Nr of relative prime pairs = %d\n", relativePrimes);
	return 0;
}
