#include "philosophers.h"


void check_all_eaten(t_handler *handler, t_philo *philo)
{
	int i;

	i = 0;
	while (i < handler->num_philosophers)
	{
		if (philo[i].nb_meals >= handler->num_times_to_eat)
			i++;
	} 
	if (i == handler->num_philosophers)
		handler->all_eat = 1;
}

/* Ve o tempo que passou desde que um dado philo comeu, se ultrapassar o tempo
de morte, avisa o handler */
void check_dead(t_handler *handler, t_philo *philo)
{
	int i;

	while (!(handler->all_eat))
	{
		i = 0;
		while (i < handler->num_philosophers && !(handler->dead))
		{
			pthread_mutex_lock(&(handler->mutex_eat_check));
			if (((__uint64_t)get_timestamp(handler) - (__uint64_t)philo[i].last_time_eat) > handler->time_to_die)
			{
				print_status(handler, i, "died");
				handler->dead = 1;
			}
			pthread_mutex_unlock(&(handler->mutex_eat_check));
			i++;
			usleep(100);
		}
		if (handler->dead)
			break ;
		check_all_eaten(handler, philo);
	}
}