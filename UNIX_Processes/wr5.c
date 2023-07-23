#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	int w, n, k = 10;	
	w = open("/tmp/abc", O_WRONLY);
	n = write(w, &k, sizeof(int));
	printf("%d\n", n);

	return 0;
}
