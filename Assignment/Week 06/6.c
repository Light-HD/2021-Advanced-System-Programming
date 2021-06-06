/* matrix multiply permutations */
#include <stdio.h>
#include <stdlib.h>

#define M 	512L
#define TEST 	10
//#define CHECK

#ifdef CHECK
void print_array(double *array, long n) {
	unsigned long i;

	for (i=0; i<n; i++) 
		printf("%lf ", array[i]);
	printf("\n");
	return;
}
#endif

	int i,j,k;
void init_array(double *array, long n) {
	unsigned long i;

	for (i=0; i<n; i++) 
		array[i] = 1.0;
		//array[i] = (rand()%100)/10.0;
	return;
}

void mult (double* a, double *b, double *c, int n) {
	int i,j,k;

	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			c[i*n+j] = 0;
			for (k=0; k<n; k++) {
				c[i*n+j] += a[i*n+k]*b[k*n+j];
			}
		}
	}
}

int main() {
	double *a = malloc(sizeof(double)*M*M);
	double *b = malloc(sizeof(double)*M*M);
	double *c = malloc(sizeof(double)*M*M);


	if (a==NULL || b == NULL || c == NULL)
		exit(1);

	init_array(a, M*M);
	init_array(b, M*M);
	for (int i = 0; i<TEST; i++)
		mult(a,b,c,M);
#ifdef CHECK
	print_array(a, M*M);
	print_array(b, M*M);
	print_array(c, M*M);
#endif
}
	

