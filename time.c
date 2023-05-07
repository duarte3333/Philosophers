#include "philosophers.h"

/* Esta funcao e uma implementacao da funcao uspleep(). 
Esta foi criada porque e mais precisa do que a funcao original.
O uso do usleep(100) serve para poupar recursos do processador,
limitando a frequencia do loop*/
void	ft_usleep(int milisec)
{
	struct timeval	time_v;
	__uint64_t		start;
	__uint64_t		end;

	gettimeofday(&time_v, NULL);
	start = (time_v.tv_sec * 1000) + (time_v.tv_usec / 1000);
	end = start + milisec;
	while (start < end)
	{
		gettimeofday(&time_v, NULL);
		start = (time_v.tv_sec * 1000) + (time_v.tv_usec / 1000);
		usleep(100);
	}
}

time_t	get_time(t_handler *handler)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, 0);
	return ((curr_time.tv_sec * 1000 + curr_time.tv_usec / 1000) \
	- handler->begin_time);
}

time_t	get_timestamp(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, 0);
	return ((curr_time.tv_sec * 1000l + curr_time.tv_usec / 1000l));
}

/* Funcao que imprime a acao atual do filosofo e o seu respetivo
tempo em milisegundos */

void print_status(t_handler *handler, int i, char *action)
{	
	//if (!check_individual(&(handler->philosophers[i])))
	int dead;

	if (handler->num_philosophers == 1)
		printf("%lu\t%i\t%s\n", (get_time(handler)), (i + 1), action);
	else
	{
		pthread_mutex_lock(&(handler->philosophers[i].mutex_life));
		dead = handler->philosophers[i].dead;
		pthread_mutex_unlock(&(handler->philosophers[i].mutex_life));
		if (!dead)
			printf("%lu\t%i\t%s\n", (get_time(handler)), (i + 1), action);
	}
}
//1 milisegundo sao 1000 microsegundos
//__uint64_t representa unsigned long long