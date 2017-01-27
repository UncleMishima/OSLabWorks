#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>

const size_t BUFFER_SIZE = 128;
const size_t SHR_SIZE = 50;

int main (void)
{
	key_t key;
	int fd;
	int shmid, id = 1212, bufLen; 
	char *shm, buffer[BUFFER_SIZE], fifoBuffer[BUFFER_SIZE];
	time_t t;
	struct tm* timeinfo;

	if ((mkfifo("file" , 0744)) < 0)
		perror("file already exists");
	
	if ((fd = open("file", O_RDWR)) < 0)
		perror("open() error");
	
	if ((key = ftok("file", id)) == (key_t)-1)
		perror("ftok() error"); 

	if ((shmid = shmget(key, SHR_SIZE, IPC_CREAT | IPC_EXCL | 0666)) < 0)
	{
		if (errno == EEXIST)
		{		
			if ((shmid = shmget(key, SHR_SIZE,  0666)) < 0)
				perror("shmget() error");
		}else
		{
			perror("shmget() error");
		}
	}
	
	if ((shm = shmat(shmid, NULL, 0)) == (char*)-1)
		perror("shmat() error");


	//bzero(&buffer, BUFFER_SIZE);
	while(1)
	{
		bufLen = strlen(buffer);
		sleep(3);

		time(&t);
		sprintf(buffer, "Time: %s\n", ctime(&t));
		if (write(fd, buffer, strlen(buffer)) < 0)
			perror("write() error");
		memcpy(shm, buffer, bufLen);
		printf("\nFile1 wrote the file\n");
 		
 		sleep(5);
		printf("File1 reading from FIFO\n");
		if (read(fd, fifoBuffer, BUFFER_SIZE) < 0)
			perror("read() error");	
		printf("%s\n\n", fifoBuffer);

		memcpy(buffer, shm, strlen(shm));
		printf("File1 reading from shared memory:\n");
		printf("%s\n\n", buffer);
		
	}

	return 0;
}
