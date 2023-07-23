#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pfd[2], i, n;
    pipe(pfd);
    for(i=0; i<3; i++) {
        if(fork() == 0) {
			close(pfd[0]); // close the reading in the child because we
			// do not need it
            write(pfd[1], &i, sizeof(int));
            close(pfd[1]); // close the writing after we finished writing
            //exit(0);
        }
        else {
            // a se vedea punctele c) si d)
        }
	}
	close(pfd[1]); // close the writing in the parent
    for(i=0; i<16; i++) {
		
        if( wait(0) == -1)
			break;
        read(pfd[0], &n, sizeof(int));
        printf("%d\n", n);
    }
    close(pfd[0]); 
    return 0;
}

