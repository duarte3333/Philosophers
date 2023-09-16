#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

//Passar argumentos para threads

//Somar todos os números com duas threads
//Uma thread soma metade e a outra soma a outra metade
int primes[10] = {2, 3, 5 ,7, 11, 13, 17, 19, 23, 29};

void*	routine(void* arg)
{
	int index = *(int*)arg;
	int sum = 0;
	int j;
	while (j < 5)
	{
		sum += primes[index + j];
		j++;
	}
	*(int*)arg = sum;
	printf("[pointer rotina arg] %p\n", arg);
	return (arg);
}

//Foi necessário alocar as variaveis que serão enviadas para a thread
//porque assim a cada iteração garantimos 4bytes para enviar para cada
//thread
int main(int ac, char **av)
{
	int 		i;
	pthread_t 	th[2];

	i = 0;
	while (i < 2)
	{
		int* a = malloc(sizeof(int));
		*a = i * 5;
		printf("a%i %p\n", i, a);
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			perror("Failed to create thread\n");
			return 1;
		}
		i++;
	}
	i = 0;
	int	global_sum = 0;
	while (i < 2)
	{
		int *result;
		if (pthread_join(th[i], &result) != 0)
		{
			perror("Failed to join thread\n");
			return 2;
		}
		printf("[pointer main] %p\n", result);
		global_sum += *result;
		free(result);
		i++;
	}
	printf("Global sum: %d\n", global_sum);
	return 0;
}
// a0 0x55ee250b22a0
// a1 0x55ee250b27f0
// [pointer rotina arg] 0x55ee250b22a0
// [pointer rotina arg] 0x55ee250b27f0
// [pointer main] 0x55ee250b22a0
// [pointer main] 0x55ee250b27f0