#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

const size_t NUM = 100;
const size_t NUM_OF_THREADS = 10;

void* calculateFib()
{
	long double fib[NUM];

	fib[0] = 0;
	fib[1] = 1;

	printf("%.Lf\n", fib[0]);
	printf("%.Lf\n", fib[1]);

	for(int i = 2; i < NUM; ++i)
	{

		fib[i] = fib[i-1] + fib[i-2];
		printf("%.Lf\n", fib[i]);
	}
}

int main()
{
	pthread_t threads[NUM_OF_THREADS];
	for (int i = 0; i < NUM_OF_THREADS; ++i)
	{
		pthread_create(&threads[i], NULL, calculateFib, NULL);
		pthread_join(threads[i], NULL);
	}

	return 0;
}
