#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void sigint_handler(int sig) {
	printf("Function pointer has problem in twice\n");
	exit(0);
}
void twice(int (*f)(int), int i) {
	signal(SIGSEGV, sigint_handler);
        printf("f(f(i)): %d\n", f(f(i)));
}

int addone(int i) {
        return i+1;
}

int main() {
    int (*f)(int);
    int *i;

    f = addone;
    twice(f, 2);

    f = 0;
    twice(f, 2);

    f = addone;
    twice(f, 3);

    i = 0;
    f = addone;
    twice(f, *i);

    return 0;
}

