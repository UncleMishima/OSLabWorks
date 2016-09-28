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
	int rv;

	time_t seconds1;
	time_t seconds2;

	switch(pid=fork()) 
	{
		case -1: perror("fork"); /* произошла ошибка */
		exit(1); /*выход из родительского процесса*/
		case 0:
		printf(" CHILD: Это процесс-потомок!\n");
		seconds1 = time(NULL);
		printf(" CHILD: Мой PID -- %d\n", getpid());
		printf(" CHILD: PID моего родителя -- %d\n", getppid());
		printf("Time for CHILD process: %ld\n", seconds1);

		printf(" CHILD: Введите мой код возврата:");
		scanf(" %d");
		//printf("Time for CHILD process: %ld\n", seconds1);
		printf(" CHILD: Выход!\n");
		exit(rv);
		default:
		printf("PARENT: Это процесс-родитель!\n");
		seconds2 = time(NULL);
		printf("PARENT: Мой PID -- %d\n", getpid());
		printf("PARENT: PID моего потомка %d\n",pid);
		printf("PARENT: Я жду, пока потомок не вызовет exit()...\n"); 
		wait(NULL);
		printf("PARENT: Код возврата потомка:%d\n", WEXITSTATUS(rv));
		printf("Time for PARENT process: %ld\n", seconds2);
		printf("PARENT: Выход!\n");
	}

	return 0;
}

