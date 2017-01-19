#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main()
{
	pid_t pid;
	int desc;
	char buf[] = "CHILD";
	size_t l = strlen(buf);
	
	if ( (desc = open("file", O_CREAT | O_TRUNC | O_WRONLY, 0744)) < 0)
	{
		printf("Error");
		return -1;
	}
	
	if ((pid = fork()) < 0) printf("Error");
	if (pid == 0)
	{	
		printf("CHILD process wrote the file\n");
		write(desc, buf, l);
	}
	else
	{
		printf("PARENT process did nothing\n");
	}

	return 0; 
}