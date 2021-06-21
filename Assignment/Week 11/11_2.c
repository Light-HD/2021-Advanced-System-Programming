#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	int status;
	pid_t pid;
	argv = argv+1;
	if ((pid = fork()) == 0){
		execve(argv[0],argv,NULL);
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
