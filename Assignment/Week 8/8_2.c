/* matrix multiply permutations */
#include <stdio.h>
#include <stdlib.h>

#define M 	8000
#define TEST 	10

void init_array(double *array, long n) {
	unsigned long i;

	for (i=0; i<n; i++) 
		array[i] = 1.0;
		//array[i] = (rand()%100)/10.0;
	return;
}

void mult (double* a, double *b, double *c, int n) {
	int i,j,k;

	for (j=0; j<n; j++) {
		for (i=0; i<n; i++) {
				c[i] += a[i*n+j]*b[i*n+j];
		}
	}
}

int main() {
	double *a = malloc(sizeof(double)*M*M);
	double *b = malloc(sizeof(double)*M*M);
	double *c = calloc(M, sizeof(double));


	if (a==NULL || b == NULL || c == NULL)
		exit(1);

	init_array(a, M*M);
	init_array(b, M*M);
	for (int i = 0; i<TEST; i++)
		mult(a,b,c,M);
}
	

