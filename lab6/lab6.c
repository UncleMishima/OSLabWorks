#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <unistd.h>


const size_t NUM = 100;
const size_t NUM_OF_THREADS = 10;
const size_t BUFF_SIZE = 256;

sem_t semVar;

void* fileReader()
{
	char buff[BUFF_SIZE];
	int desc, buffer_read;
	if ((desc = open("file", O_CREAT | O_RDONLY, 0744)) < 0)
	{
		printf("Error");
	}
		sleep(1);
		bzero(buff, BUFF_SIZE);
	
	while(1)
	{
		lseek(desc, 0, SEEK_SET);
		sem_wait(&semVar);
		while((buffer_read = read(desc, buff, BUFF_SIZE)) > 0)
		{
			printf("%s\n",buff);
		}
	
		sem_post(&semVar);
		sleep(6);
	}
}

void* fileWriter()
{
	struct tm* Time;
	time_t t; 
	int stringNum = 0;
	char buff[BUFF_SIZE];
	int desc;
	if ((desc = open("file", O_CREAT | O_WRONLY | O_TRUNC, 0744)) < 0)
	{
		printf("Error");
	}
	
	while(1)
	{
		sem_wait(&semVar);
		time(&t);
		Time = localtime(&t);
		sprintf(buff, "String number: %d Time: %d:%d:%d\n", stringNum, Time->tm_hour, Time->tm_min, Time->tm_sec);
		write(desc, buff, strlen(buff));
		stringNum++;
		sem_post(&semVar);

		sleep(2);
	}
}


int main()
{
	pthread_t readThreads[NUM_OF_THREADS];
	pthread_t writeThread;
	
	sem_init(&semVar, 0, 2);

	pthread_create(&writeThread, NULL, fileWriter, NULL);

	for (int i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_create(&readThreads[i], NULL, fileReader, NULL);
	}

	pthread_join(writeThread, NULL);

	for (int i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_join(readThreads[i], NULL);
	}

	return 0;
}
