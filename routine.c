#include "philosophers.h"


/* This function puts the philos sleeping */
void	to_sleep(t_philo *philo)
{
	int i;

	i = philo->philo_id;

	printf("Tou a dormir e sou o %i\n", (i + 1));
	ft_usleep(philo->handler->time_to_sleep);
}

/* This function puts the philos thinking */
void	think(t_philo *philo)
{
	int i;

	i = philo->philo_id;

	printf("Tou a pensar e sou o %i\n", (i + 1));
}

/* The eat function locks two forks' mutexes for a philosopher, 
prints a message indicating the philosopher is eating, sleeps 
for a specified time period, and then releases the two mutexes. 
In case of 5 philos, the first fork will be 0 and take i=0 and (0+1 % 5)=0
The last philo will be 4 and first fork will be i=4 and the second
fork will be (4+1 % 5) = 0*/


void	eat(t_philo *philo)
{
	int i;
	struct timeval	time_v;

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
	gettimeofday(&time_v, NULL);
	philo->last_time_eat = (time_v.tv_sec * 1000) + (time_v.tv_usec / 1000);
	if (i < (philo->handler->num_philosophers - 1))
	{
		pthread_mutex_unlock(&(philo->handler->forks[i]));
		pthread_mutex_unlock(&(philo->handler->forks[(i + 1) % philo->handler->num_philosophers]));
	}	
	else //caso seja o ultimo
	{
		pthread_mutex_unlock(&(philo->handler->forks[(i + 1) % philo->handler->num_philosophers]));
		pthread_mutex_unlock(&(philo->handler->forks[i]));
	}
	//printf("[lastly] %u\n", philo->last_time_eat);

}

int check_dead(t_philo *philo)
{
	int i;

	struct timeval	time_v;
	int				crr_time;
	gettimeofday(&time_v, NULL);
	crr_time = (time_v.tv_sec * 1000) + (time_v.tv_usec / 1000);

	i = philo->philo_id;
	printf("\n[curr] %i\n", crr_time);
	printf("[last] %i\n", philo->last_time_eat);
	printf("[sum] %i\n", crr_time - philo->last_time_eat);
	printf("[ttd] %i\n", philo->handler->time_to_die);

	if ((crr_time - philo->last_time_eat) > philo->handler->time_to_die)
	{
		//philo->handler->dead = 1;
		printf("Alguem morreu");
		return (0);
	}
	return (1);
	
}

void *routine(void *arg) 
{
	long long int i;
	t_philo *philo;
	philo = (t_philo*)arg;
	while (philo->nb_meals && check_dead(philo))
	{
		eat(philo);
		to_sleep(philo);
		think(philo);
		(philo->nb_meals)--;
	}
    return NULL;
}