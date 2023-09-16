#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

//Passar argumentos para threads

//Cada thread receberá um número primo
int primes[10] = {2, 3, 5 ,7, 11, 13, 17, 19, 23, 29};

void*	routine(void* arg)
{
	int index = *(int*)arg;
	printf("[nb] %d \n", primes[index]);
	free(arg);
}

//Foi necessário alocar as variaveis que serão enviadas para a thread
//porque assim a cada iteração garantimos 4bytes para enviar para cada
//thread
int main(int ac, char **av)
{
	int 		i;
	pthread_t 	th[10];

	while (i < 10)
	{
		int* a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			perror("Failed to create thread\n");
			return 1;
		}
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread\n");
			return 2;
		}
		i++;
	}
	return 0;
}

//-------------------------------------------
//-  mainthread  -   thread 1   -   thread2
//-------------------------------------------
//     i = 0     -              -    
//-------------------------------------------
//               -   created    -
//-------------------------------------------
//               -              -  created
//-------------------------------------------
//     i = 1     -              -
//-------------------------------------------
//               -   i is 1     - 
//               -   print 3    -  
//-------------------------------------------
//               -              -  i is 1
//               -              -  print 3
//-------------------------------------------

//Houve primeiro o incremento do i do que
//a execução da rotina da thread 1

//Se corresse tudo bem:
//-------------------------------------------
//-  mainthread  -   thread 1   -   thread2
//-------------------------------------------
//     i = 0     -              -    
//-------------------------------------------
//               -   created    -
//-------------------------------------------
//               -   i is 0     -  
//               -   print 2    -  
//-------------------------------------------
//     i = 1     -              -
//-------------------------------------------
//               -              -  created
//-------------------------------------------
//               -              -  i is 1
//               -              -  print 3
//-------------------------------------------
//               -              -
//-------------------------------------------
//               -              -
//-------------------------------------------