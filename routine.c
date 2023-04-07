#include "philosophers.h"

long long int o = 0;

void	a_sleep(t_philo *philo)
{
	//__uint64_t	ms;
	int i;

	i = philo->philo_id;

	printf("Tou a dormir e sou o %i\n", (i + 1));
	ft_usleep(philo->handler->time_to_sleep);
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
	ft_usleep(philo->handler->time_to_eat);
	pthread_mutex_unlock(&(philo->handler->forks[i]));
	pthread_mutex_unlock(&(philo->handler->forks[(i + 1) % philo->handler->num_philosophers]));
}

void *routine(void *arg) 
{
	long long int i;
	t_philo *philo;
	philo = (t_philo*)arg;
	while (philo->nb_meals)
	{
		eat(philo);
		//a_sleep(philo);
		(philo->nb_meals)--;
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