#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(){
	int arr[100] = {0};
	int sizeArr = 0;
	// reading the size of the array to the fifo
	int fin = open("/tmp/sum", O_RDONLY);
	if(fin == -1)
		return 10;
	if(read(fin, &sizeArr, sizeof(int)) == -1)
		return 20;
	printf("Read %d\n", sizeArr);	
	// reading sizeArr elements to the fifo
	if(read(fin, arr, sizeof(int) * sizeArr) == -1)
		return 30;
	close(fin); // close the reading
	
	// computing the sum
	int sum = 0;
	for(int i = 0; i < sizeArr; i++){
		printf("Received %d\n", arr[i]);
		sum += arr[i];
	}
	printf("Sum send - %d\n", sum);
	int fout = open("/tmp/sum", O_WRONLY);
	if(fout == -1)
		return 40;
	if(write(fout, &sum, sizeof(int)) == -1)
		return 50;
	close(fout);
	
	return 0;
}

