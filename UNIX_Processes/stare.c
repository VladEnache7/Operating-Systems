#include <stdio.h>
#include <signal.h>

// informatii globale de stare
   long long int  numar;

void  tipareste_stare(int semnal) {
// Tipareste informatiile de stare solicitate
   printf("Numar= %lld\n", numar);
}//handlerul de semnal

main() {
   printf("PID = %d\n", getpid());
	signal(SIGUSR1,tipareste_stare);
    //- - -
   for(numar=0; ; numar++) {
    
    // - - - 
    
   }//for
}//main

