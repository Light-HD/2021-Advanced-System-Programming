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
	int in = 0, inj;
	double t0, t1;
	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) {
			inj = in+j;
			t0 = 0;
			t1 = 0;
			for (k=0; k<n; k+=2) {
				t0 = t0+a[in+k]*b[k*n+j];
				t1 = t1+a[in+k+1]*b[(k+1)*n+j];
			}
		c[inj] = t0 + t1;
		}
	in += n;
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
	

