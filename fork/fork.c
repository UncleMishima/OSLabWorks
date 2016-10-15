#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

main() 
{
	pid_t pid;

	clock_t sec1;
	clock_t sec2;

	switch(pid=fork()) 
	{
		case -1: perror("fork");
		exit(1);
		case 0:
		sec1 = time(NULL);
		printf("CHILD: PID -- %d\n", getpid());
		printf("CHILD: PARENT PID  -- %d\n", getppid());
		printf("Time for CHILD process: %ld seconds\n", sec1/60);
		default:
		sec2 = time(NULL);
		printf("PARENT: MY PID -- %d\n", getppid());
		printf("PARENT: CHILD PID -- %d\n", getpid());
		printf("Time for PARENT process: %ld seconds\n", sec2/60);
	}

	return 0;
}

