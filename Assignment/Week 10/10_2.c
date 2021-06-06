#include <stdio.h>
#include <malloc.h>

int main() {
	int *buf = calloc(10,sizeof(int));	
	free(buf);
}
