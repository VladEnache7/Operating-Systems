#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
	int arr[] = {1, 2, 3, 4, 5};
	int sizeArr = sizeof(arr) / sizeof(int);
	// first writing the size of the array to the fifo
	int fout = open("/tmp/sum", O_WRONLY);
	if(fout == -1)
		return 1;
	if(write(fout, &sizeArr, sizeof(int)) == -1)
		return 2;
	
	// writing sizeArr elements to the fifo
	if(write(fout, arr, sizeof(int) * sizeArr) == -1)
		return 3;
	close(fout); // close the writing
	
	// reading the sum from fifo
	int sum;
	int fin = open("/tmp/sum", O_RDONLY);
	if(fin == -1)
		return 4;
	if(read(fin, &sum, sizeof(int)) == -1)
		return 5;
	close(fin);
	printf("The sum received is %d\n", sum); 
	return 0;
}

