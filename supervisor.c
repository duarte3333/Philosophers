#include "philosophers.h"

static int check_eaten(t_handler *handler, t_philo *philo, int *j)
{
	pthread_mutex_lock(&philo->mutex_eat_check);
	*j += (philo->nb_meals >= handler->num_times_to_eat);
	if (get_timestamp() > philo->time_of_life)
	{	
		handler->dead = 1;
		print_status(handler, philo->philo_id, "died");
		//exit(0);
	}
	pthread_mutex_unlock(&philo->mutex_eat_check);
	return (handler->dead);
}

static void *kill_philo(t_handler *handler)
{
	int i;

	i = 0;
	while (i < handler->num_philosophers)
	{
		pthread_mutex_lock(&handler->philosophers[i].mutex_life);
		handler->philosophers[i].dead = 1;
		pthread_mutex_unlock(&handler->philosophers[i].mutex_life);
		i++;
	}
	return (handler);
}

/* Esta funcao permite ver se o philo esta morte, 
durante esta verificacao tem de se garantir que o philo nao esta
a comer */
void *supervisor(void *arg)
{
	t_handler 	*handler;
	int 		i;
	int			j;
	
	handler = (t_handler*)arg;
	while (1)
	{
		i = -1;
		j = 0;
		while (++i < handler->num_philosophers)
		{
			if (check_eaten(handler, &(handler->philosophers[i]), &j))
				return (kill_philo(handler));
			usleep(100);
		}
		usleep(100);
		if (j == (handler->num_philosophers))
			return (kill_philo(handler));
		usleep(100);
	}
}
