#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[], char *envp[]) {
    int status;
    pid_t pid;
    char *myarg[3];
    int p1,p2,p3;
    p1 = fork();
    p2 = fork();
    p3 = fork();
    printf("%d: %d,%d,%d\n",getpid(),p1,p2,p3);
}

