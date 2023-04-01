#include "philosophers.h"

long long int o = 0; 

//1 milisegundo sao 1000 microsegundos
void	ft_time(int time)
{
	struct timeval start;
    unsigned long long elapsed_time;

    gettimeofday(&start, NULL);
    usleep(time*1000);
}

void	eat(t_philo *philo)
{
	int i;

	i = philo->philo_id;
	if (i < (philo->handler->num_philosophers - 1))
	{
		pthread_mutex_lock(&(philo->handler->forks[i]));
		pthread_mutex_lock(&(philo->handler->forks[(i + 1) % philo->handler->num_philosophers]));
	}	
	else //caso seja o ultimo
	{
		pthread_mutex_lock(&(philo->handler->forks[(i + 1) % philo->handler->num_philosophers]));
		pthread_mutex_lock(&(philo->handler->forks[i]));
	}
	printf("Tou a comer e sou o %i\n", (i + 1));
	ft_time(philo->handler->time_to_eat);
	pthread_mutex_unlock(&(philo->handler->forks[i]));
	pthread_mutex_unlock(&(philo->handler->forks[(i + 1) % philo->handler->num_philosophers]));
}

void *routine(void *arg) 
{
	long long int i;
	t_philo *philo;
	philo = (t_philo*)arg;
	while (philo->handler->num_times_to_eat)
	{
		eat(philo);
	}
	// i = 0;
	// //eat(handler);
	// while (i < 100)
	// {
	// 	//pthread_mutex_lock(&(handler->my_mutex));
    // 	//printf("Thread is %i executing \n", i);
	// 	o++;
	// 	i++;
	// 	//pthread_mutex_unlock(&(handler->my_mutex));
	// }
	// //pthread_mutex_lock(&(handler->my_mutex));
	// printf("[i] %lli, [o] %lli\n", i, o);
	// //pthread_mutex_unlock(&(handler->my_mutex));
    return NULL;
}