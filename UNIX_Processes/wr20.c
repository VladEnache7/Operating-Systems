#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

int n = 0;
pthread_mutex_t m[3];

void* f(void* p){
	int id = (int) p;
		
	pthread_mutex_lock(&m[id]);
	n += id;
	printf("%d ", n);
	pthread_mutex_unlock(&m[(id + 1) % 3]);
	return NULL;
}


int main(){
	int i;
	pthread_t t[3];

	for(i = 0; i < 3; i++)
		pthread_mutex_init(&m[i], NULL);
	
	pthread_mutex_lock(&m[0]);
	pthread_mutex_lock(&m[2]);

	for(i = 0; i < 3; i++){
		pthread_create(&t[i], NULL, f, (void*) i);
}

	for(i = 0; i < 3; i++)
		pthread_join(t[i], NULL);

	for(i = 0; i < 3; i++)
		pthread_mutex_destroy(&m[i]);	

	return 0;
}
