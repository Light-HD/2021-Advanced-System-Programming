#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int status;
	pid_t pid;
	char *a[] = {argv[1],argv[2],NULL};
	if ((pid = fork()) == 0){
		execve(a[0],a,NULL);
		exit(1);
	}
	else {
		pid = waitpid(pid,&status,0);
		if (WIFEXITED(status)){
			printf("child %d terminated by parent %d normally with exit status=%d\n", 
				pid, getpid(), WEXITSTATUS(status)); 
		}
	}

}
