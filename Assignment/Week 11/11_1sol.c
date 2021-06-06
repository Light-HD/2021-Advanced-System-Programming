#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[], char *envp[]) {
    int status1,status2,status3, i;
    int get1,get2,get3;
    char *myarg[3];
    pid_t pid[7];
    int p1,p2,p3 ;
    p1 = fork();
    p2 = fork();
    p3 = fork();
    printf("%d: %d,%d,%d\n",getpid(),p1,p2,p3);
    pid_t wpid1 = waitpid(p1, &status1, 0);
    pid_t wpid2 = waitpid(p2, &status2, 0);
    pid_t wpid3 = waitpid(p3, &status3, 0);
    if (WIFEXITED(status1))
	if(wpid1 != -1)
		printf("child %d terminated by parent %d normally with exit status=%d\n",
			wpid1, getpid(), WEXITSTATUS(status1));   
    if (WIFEXITED(status2))
	if(wpid2 != -1)
		printf("child %d terminated by parent %d normally with exit status=%d\n",
			wpid2, getpid(), WEXITSTATUS(status2));
    if (WIFEXITED(status3))
	if(wpid3 != -1)
		printf("child %d terminated by parent %d normally with exit status=%d\n",
			wpid3, getpid(), WEXITSTATUS(status3));
}

