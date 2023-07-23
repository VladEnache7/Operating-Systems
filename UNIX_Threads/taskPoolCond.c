#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_NUM 8
 
typedef struct{
	int a, b;
}Task;

Task taskQueue[256];
int tasksNr;
pthread_mutex_t mutexStack = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condTasks = PTHREAD_COND_INITIALIZER;


void* threadExecute(void* arg){
	int index = (int) arg;
	while(1){

		pthread_mutex_lock(&mutexStack);
		
		while(tasksNr == 0){
			pthread_cond_wait(&condTasks, &mutexStack); // wait for a signal of a task submitted
		}

		Task task = taskQueue[--tasksNr]; 
	
		pthread_mutex_unlock(&mutexStack);

		// executing the task
		printf("T%d -> %d + %d = %d\n", index, task.a, task.b, task.a + task.b);
		sleep(1); // the task takes a while
	}
	return NULL;
}

void* threadSubmit(void* arg){
	int index = (int) arg;
	while(1){
		
		// creating a task
		Task task;
		task.a = rand() % 100;
		task.b = rand() % 100;
		sleep(1);

		// submitting the task
		pthread_mutex_lock(&mutexStack);
	
		taskQueue[tasksNr++] = task; 
	
		pthread_mutex_unlock(&mutexStack);
		
		printf("T%d - submitted %d & %d\n", index, task.a, task.b);
		
		pthread_cond_signal(&condTasks); // signal that a task have been submited
	}
	return NULL;
}

int main(){
	pthread_t t[THREAD_NUM];
	

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

	
	return 0;
}
