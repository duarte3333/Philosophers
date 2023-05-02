#include "philosophers.h"

void	new_sleep(long long time, t_handler *handler)
{
	long long i;

	i = get_timestamp(handler);
	while (!(handler->dead))
	{
		if ((i - get_timestamp(handler)) >= time)
			break ;
		usleep(50);
	}
}

/* Esta funcao coloca o philo a dormir*/
void to_sleep(t_philo *philo)
{
	print_status(philo->handler, philo->philo_id, "is sleeping");
	//ft_usleep(philo->handler->time_to_sleep);
	new_sleep(philo->handler->time_to_sleep, philo->handler);
}

/* Esta funcao coloca o philo a pensar*/
void think(t_philo *philo)
{
	print_status(philo->handler, philo->philo_id, "is thinking");
}

/* A função bloqueia os mutexes de dois garfos para um filósofo, 
da print da mensagem que esta a comer e espera o tempo que precisa para comer.
O ultimo tempo em que comeram e atualizado com um mutex para garantir que 
esta correto. */
void eat(t_philo *philo)
{
	int i;
	struct timeval time_v;

	i = philo->philo_id;
	//philo->time_of_life = philo->handler->time_to_eat + get_time(philo->handler);
	if (i < (philo->handler->num_philosophers - 1))
	{
		pthread_mutex_lock(&(philo->handler->forks[i]));
		pthread_mutex_lock(&(philo->handler->forks[(i + 1) % philo->handler->num_philosophers]));
	}
	else // caso seja o ultimo
	{
		pthread_mutex_lock(&(philo->handler->forks[(i + 1) % philo->handler->num_philosophers]));
		pthread_mutex_lock(&(philo->handler->forks[i]));
	}
	print_status(philo->handler, philo->philo_id, "has taken a fork");
	print_status(philo->handler, philo->philo_id, "has taken a fork");
	print_status(philo->handler, philo->philo_id, "is eating");
	pthread_mutex_lock(&philo->handler->mutex_eat_check);
	philo->last_time_eat = get_timestamp(philo->handler);
	pthread_mutex_unlock(&philo->handler->mutex_eat_check);
	//ft_usleep(philo->handler->time_to_eat);
	new_sleep(philo->handler->time_to_eat, philo->handler);
	philo->nb_meals++;
	if (i < (philo->handler->num_philosophers - 1))
	{
		pthread_mutex_unlock(&(philo->handler->forks[i]));
		pthread_mutex_unlock(&(philo->handler->forks[(i + 1) % philo->handler->num_philosophers]));
	}
	else // caso seja o ultimo
	{
		pthread_mutex_unlock(&(philo->handler->forks[(i + 1) % philo->handler->num_philosophers]));
		pthread_mutex_unlock(&(philo->handler->forks[i]));
	}
}

void *routine(void *arg)
{
	long long int i;
	t_philo *philo;
	philo = (t_philo *)arg;
	//philo->time_of_life = philo->handler->time_to_eat + get_time(philo->handler);
	while (!(philo->handler->dead))//&& !anyone_die(philo))
	{
		eat(philo);
		if (philo->handler->all_eat)
			break;
		to_sleep(philo);
		think(philo);
	}
	return NULL;
}