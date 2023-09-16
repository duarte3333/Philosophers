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
	if (pthread_mutex_trylock(&mutex) == 0)
	{
		printf("Got lock\n");
		sleep(1);
		pthread_mutex_unlock(&mutex);
	}
	else
		printf("Didn't get lock \n");
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
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (pthread_join(t[i], NULL) != 0)
			return 2;
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return 0;
}