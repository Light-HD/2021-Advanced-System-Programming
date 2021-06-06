/* matrix multiply permutations */
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#define M 	10
#define TEST 	1
#define CHECK

#ifdef CHECK
void print_array(double *array, long n) {
	unsigned long j,i;

	for (i=0; i<n; i++) {
		for (j=0; j<n; j++) 
			printf("%.3lf ", array[i*n+j]);
		printf("\n");
	}
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

/*
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
*/

int main() {
	void *handle;
	void (*mult)(double *, double *, double *, int);
	char *error;
	handle = dlopen("./libmult.so",RTLD_LAZY);
	if(!handle){
		fprintf(stderr,"%s\n",dlerror());
		exit(1);
	}
	mult = dlsym(handle, "mult");
	if((error = dlerror()) != NULL){
		fprintf(stderr, "%s\n", error);
		exit(1);
	}
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
	print_array(a, M);
	print_array(b, M);
	print_array(c, M);
#endif
	if(dlclose(handle) < 0) {
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	return 0;
}
	

