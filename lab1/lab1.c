#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid;
	
	if ((pid= fork()) < 0) printf("Error");
	if (pid == 0)
	{	
		printf("CHILD process\nMy PID: %d \nPID of my parent: %d \n", pid, getppid());
	}
	else
	{
		printf("PARENT process\nMy PID: %d \nPID of my child: %d \n", getpid(), pid);
	}

	return 0; 
}