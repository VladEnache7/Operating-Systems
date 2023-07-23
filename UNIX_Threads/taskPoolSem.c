#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_NUM 4

typedef struct{
	int a, b;
}Task;

Task taskQueue[256];
int tasksNr;
pthread_mutex_t mutexQueue = PTHREAD_MUTEX_INITIALIZER;

sem_t semEmpty;
sem_t semFull;

void* threadExecute(void* arg){
	int index = (int) arg;
	while(1){
		sem_wait(&semFull); // wait for a task to be posted

		pthread_mutex_lock(&mutexQueue);
	
		Task task = taskQueue[--tasksNr]; 
	
		pthread_mutex_unlock(&mutexQueue);

		// executing the task
		printf("T%d -> %d + %d = %d\n", index, task.a, task.b, task.a + task.b);
		
		sem_post(&semEmpty);
		
		sleep(1); // the task takes a while
	}
	return NULL;
}

void* threadSubmit(void* arg){
	int index = (int) arg;
	while(1){
		sem_wait(&semEmpty);
		// creating a task
		Task task;
		task.a = rand() % 100;
		task.b = rand() % 100;
		sleep(1);
		// submitting the task
		pthread_mutex_lock(&mutexQueue);
	
		taskQueue[tasksNr++] = task; 
	
		pthread_mutex_unlock(&mutexQueue);
		
		printf("T%d - submitted %d & %d\n", index, task.a, task.b);
		sem_post(&semFull); // post that a task was submitted
		
	}
	return NULL;
}

int main(){
	pthread_t t[THREAD_NUM];
	
	sem_init(&semFull, 0, 0); // at first there are no tasks
	sem_init(&semEmpty, 0, 256); 	// 256 free places for tasks
	
	// creating the threads
	for(int i = 0; i < THREAD_NUM; i++){
		if(i % 2 == 0)
			pthread_create(&t[i], NULL, &threadExecute, i);
		else
			pthread_create(&t[i], NULL, &threadSubmit, i);

	}
	
	// joining the threads
	for(int i = 0; i < THREAD_NUM; i++)
		pthread_join(t[i], NULL);

	sem_destroy(&semFull);
	sem_destroy(&semEmpty);
	return 0;
}
