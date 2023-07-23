#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define nrCars 5
#define nrFuelers 1

int fuel = 0;
// initialization & destroy is done automatically
pthread_mutex_t mutexFuel = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condFuel = PTHREAD_COND_INITIALIZER;

int index[nrCars];

// variable to store number of cars waiting
int carWaiting = 0;
pthread_mutex_t mutexCars = PTHREAD_MUTEX_INITIALIZER;

void* car(void* arg){
	int carNr = *(int*) arg;
	
	printf("C%d - arrived at gas station\n", carNr);
	
	// anouncing that is waiting
	pthread_mutex_lock(&mutexCars);
	carWaiting++;
	printf("-- Nr of cars waiting: %d--\n", carWaiting);
	pthread_mutex_unlock(&mutexCars);

	// locking the mutex to try filling car tank
	pthread_mutex_lock(&mutexFuel);	

	while(fuel < 40){
		printf("C%d - waiting for more fuel\n", carNr);
		pthread_cond_wait(&condFuel, &mutexFuel);
	}

	fuel -= 40;
	printf("C%d - got fuel - leaving.\n --> Fuel left = %d\n", carNr, fuel);
	pthread_mutex_unlock(&mutexFuel);

	pthread_mutex_lock(&mutexCars);
	carWaiting--;
	printf("Nr of cars waiting: %d\n", carWaiting);
	pthread_mutex_unlock(&mutexCars);
}

void* fueler(void* arg){
	int fuelerNr = *(int*) arg;

	sleep(1); // waiting for the cars to arrive

	printf("Fueler %d started his job\n", fuelerNr);

	while(carWaiting > 0){
		// filling the gas tanks
		pthread_mutex_lock(&mutexFuel);
		fuel += 15;
		printf("Fueler %d filled => fuel = %d\n", fuelerNr, fuel);
		sleep(1);
		pthread_mutex_unlock(&mutexFuel);
		
		// singaling to the cars that fuel was added
		pthread_cond_broadcast(&condFuel);
		printf("Fueler %d announced all the cars\n", fuelerNr);
	}
	printf("Fueler %d finished his job\n", fuelerNr);
}

int main(){
	pthread_t c[nrCars], f[nrFuelers];	

	// creating the cars	
	for(int i = 0; i < nrCars; i++){
		index[i] = i + 1;
		pthread_create(&c[i], NULL, &car, &index[i]);
	}

	// creating the fuelers
	for(int i = 0; i < nrFuelers; i++){
		pthread_create(&f[i], NULL, &fueler, &index[i]);
	}
	

	// joining the cars
	for(int i = 0; i < nrCars; i++){
		pthread_join(c[i], NULL);
	}
	// joining the fuelers
	for(int i = 0; i < nrFuelers; i++){
		pthread_join(f[i], NULL);
	}


	return 0;
}
