#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
sigjmp_buf buf;

void sigint_handler(int sig) {
	printf("Function pointer has problem in twice\n");
	siglongjmp(buf,1);
	exit(0);
}
void twice(int (*f)(int), int i) {
	signal(SIGSEGV, sigint_handler);
	if(sigsetjmp(buf,1));
	else printf("f(f(i)): %d\n", f(f(i)));
	signal(SIGSEGV, SIG_DFL);
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

    f = 0;
    twice(f, 2);

    i = 0;
    f = addone;
    twice(f, *i);

    return 0;
}

