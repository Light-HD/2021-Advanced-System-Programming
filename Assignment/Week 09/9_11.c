/* matrix multiply permutations */
#include <stdio.h>
#include <stdlib.h>

#define M 	5300
#define TEST 	10

typedef struct st {
	double point;
	char name[24];
} mystruct;

void init_struct(mystruct *array, long n) {
	unsigned long i;

	for (i=0; i<n; i++) 
		array[i].point = (double)(i%100);
	return;
}

void init_array(double *array, long n) {
	unsigned long i;

	for (i=0; i<n; i++) 
		array[i] = (double)(i%100);
	return;
}

void mult (double* a, mystruct *b, double *c, double *r, int n) {
	int i,j,k;

	for (j=0; j<n; j=j+1) {
		for (i=0; i<n; i=i+1) {
			r[i*n+j] += c[j*n+i]+a[i*n+j]*b[j*n+i].point;
		}
	}
}

int main() {
	double *a = malloc(M*M * sizeof(double));
	mystruct *b = malloc(M*M *sizeof(mystruct));
	double *c = malloc(M*M * sizeof(double));
	double *r = malloc(M*M * sizeof(double));
	int i,j;

	init_array(a,M*M);
	init_struct(b,M*M);
	init_array(c,M*M);
	init_array(r,M*M);

	if (a==NULL || b == NULL || c == NULL || r == NULL){
		printf("%p, %p, %p\n", a,b,c);
		exit(1);
	}

	for (int i = 0; i<TEST; i++)
		mult(a,b,c,r,M);

	#ifdef PRINT
	double sum = 0.0;
	for (j=0; j<M; j=j+1) {
		for (i=0; i<M; i=i+1) {
			printf("%.1lf ",r[i*M+j]);
			sum = sum+r[i*M+j];
		}
		printf("\n");
	}
	printf("sum: %.1lf",sum);
	#endif

}
	

