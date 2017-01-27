#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>

const size_t BUFFER_SIZE = 128;
const size_t SHR_SIZE = 50;

int main(void)
{
	key_t key;
	int fd, shmid, id = 1212;
	char *shm, buffer[BUFFER_SIZE], fifoBuffer[BUFFER_SIZE];
	time_t t;

	if (mkfifo("file", 0744) < 0)
		perror("file already exists\n");

	if ((fd = open("file", O_RDWR)) < 0)
		perror("open() failed");
	
	if ((key = ftok("file", id)) == (key_t) -1)
		perror("ftok() failed");

	if ((shmid = shmget(key, SHR_SIZE, IPC_CREAT | IPC_EXCL | 0666)) < 0)
	{
		if (errno == EEXIST)
		{		
			if ((shmid = shmget(key, SHR_SIZE,  0666)) < 0)
				perror("shmget() failed");
		}
		else
		{
			perror("shmget() failed");
		}
	}

	if ((shm = shmat(shmid, NULL, 0)) == (char*)-1)
		perror("shmat() failed");
	
	//bzero(&fifoBuffer, BUFFER_SIZE);
	while(1)
	{
		while (read(fd, fifoBuffer, BUFFER_SIZE) <= 0)
			usleep(1000);

		sleep(2);
		printf("File2 reading from FIFO:\n");
		printf("%s\n\n", fifoBuffer);
		
		write(fd, fifoBuffer, strlen(fifoBuffer));
		memcpy(buffer, shm, strlen(shm));
		printf("File2 reading from shared memory:\n");
		printf("%s\n\n", buffer);

		sleep(4);
		time(&t);
		sprintf(buffer, "Time: %s\n", ctime(&t));
		
		if (write(fd, fifoBuffer, strlen(fifoBuffer)) < 0)
			perror("write() failed");
		
		memcpy(shm, buffer, strlen(buffer));
		printf("\nFile2 wrote the file\n");	
		
	}
	return 0;
}
