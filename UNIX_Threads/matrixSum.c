#include <pthread.h>
#include <stdio.h>

int ma[20][20];
int n, m;

// This function is called by each thread to compute the sum of the elements of a row.
void *compute_row_sum(void *arg) {
		int row = (int)arg;
		printf("T%d - started\n", row);
		int sum = 0;
		for (int i = 0; i < m; i++) {
				sum += ma[row][i];
		}
		printf("T%d - got sum = %d\n", row, sum);
		return sum;
}

int main() {
	pthread_t t[20];
	
	printf("nr of rows = ");
	scanf("%d", &n);
	printf("nr of collumns = ");
	scanf("%d", &m);

	// Read a matrix of M rows and N columns.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("m[%d][%d] = ", i, j);
			scanf("%d", &ma[i][j]);
		}
	}

	// creating the threads	
	for (int i = 0; i < n; i++) {
		pthread_create(&t[i], NULL, &compute_row_sum, i);
	}

	// Join all of the threads.
	int sum = 0;
	for (int i = 0; i < n; i++) {
		int thread_sum;
		pthread_join(t[i], &thread_sum);
		sum += thread_sum;
		
	}

	// Print the sum of the elements of the matrix.
	printf("The sum of the elements of the matrix is %d\n", sum);

	return 0;
}

