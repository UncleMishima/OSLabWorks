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
	ssize_t l = strlen(buf);
	
	if ( (desc = open("file", O_CREAT | O_WRONLY, 0744)) < 0)
	{
		printf("Error");
		return -1;
	}
	
	if ((pid = fork()) < 0) printf("Error");
	if (pid == 0)
	{	
		printf("\nCHILD process wrotes the file\n");
		write(desc, buf, l);
	}
	else
	{
		printf("\nPARENT process\n");
	}

	return 0; 
}