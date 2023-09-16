#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

//Colocar codigo em assembly: cc -S <file>.c

//Data races
int mails = 0;
pthread_mutex_t mutex;

void* routine()
{
	for (int i = 0; i < 1000000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
}

//São necessários loops diferentes para o thread_create e o thread_join, 
//porque se forem feitos no mesmo loop não irá existir paralelismo
int main(int ac, char **av)
{
	int i;
	pthread_t t[3];
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < 3)
	{
		if (pthread_create(&t[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread\n");
			return 1;
		}
		printf("Thread %i started\n", i);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (pthread_join(t[i], NULL) != 0)
			return 2;
		printf("Thread %i ended\n", i);
		i++;
	}
	printf("Numbers of mails: %d\n", mails);
	pthread_mutex_destroy(&mutex);
	return 0;
}