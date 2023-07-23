#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define n 20

char* str[n] = {"one1", "two2", "three3", "four4", "five5", "six6", "seven7", "eight8", "nine9", "ten10", "eleven11", "twelve12", "thirteen13", "fourteen14", "fifteen15", "sixteen16", "seventeen17", "eighteen18", "nineteen19", "twenty20"};

int vowels, digits; 
pthread_mutex_t v = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t d = PTHREAD_MUTEX_INITIALIZER;

void* thread(void* arg){
	char* s = (char*) arg;
	printf("T ~%s~ - started\n", s);
	
	int localVowels = 0, localDigits = 0;	
	// processing it
	for(int i = 0; s[i]; i++){
		if(strchr("AEIOUaeiou", s[i]) != NULL){
			localVowels++;
		}
		else if(s[i] >= '0' && s[i] <= '9'){
			localDigits++;
		}
	}
	printf("T ~%s~ - exiting\n", s);
	
	// adding the number of vowels found to the global nr of vowels
	pthread_mutex_lock(&v);
	vowels += localVowels;
	pthread_mutex_unlock(&v);

	// adding the # digits
	pthread_mutex_lock(&d);
	digits += localDigits;
	pthread_mutex_unlock(&d);
}

void* thread1(void* arg){
	char* s = (char*) arg;
	printf("T ~%s~ - started\n", s);
}


int main(){
	pthread_t t[n];
	
	// creating the threads
	for(int i = 0; i < n; i++){
		//printf("Parent sending ~%s~ ~%p~\n", str[i], &str[i]);
		pthread_create(&t[i], NULL, &thread,(void*) str[i]);
	}
	printf("Parent - all threads created\n");
	
	// joining them
	for(int i = 0; i < n; i++){
		pthread_join(t[i], NULL);
	}
	printf("Parent - all threads joined\n");
	
	printf("# vowels = %d, # digits = %d\n", vowels, digits);
	return 0;
}
