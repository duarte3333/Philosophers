#include "philosophers.h"

/* A função bloqueia os mutexes de dois garfos para um filósofo, 
da print da mensagem que esta a comer e espera o tempo que precisa para comer.
O ultimo tempo em que comeram e atualizado com um mutex para garantir que 
esta correto. */
void eat(t_philo *philo)
{
	lock_forks(philo);
	print_status(philo->handler, philo->philo_id, "has taken a fork");
	print_status(philo->handler, philo->philo_id, "has taken a fork");
	print_status(philo->handler, philo->philo_id, "is eating");
	pthread_mutex_lock(&philo->mutex_eat_check);
	philo->time_of_life = get_timestamp() + philo->handler->time_to_die;
	philo->nb_meals++;
	pthread_mutex_unlock(&philo->mutex_eat_check);
	ft_usleep(philo->handler->time_to_eat);
	unlock_forks(philo);	
}

/* O philo esta ver se morreu ou nao com base nas informacoes do handler */
int	check_individual_life(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mutex_life));
	if (philo->dead)
	{
		pthread_mutex_unlock(&(philo->mutex_life));
		return (1);
	}
	pthread_mutex_unlock(&(philo->mutex_life));
	return (0);
}

void *routine(void *arg)
{
	t_philo *philo;
	t_handler *handler;
	philo = (t_philo *)arg;
	handler = philo->handler;
	pthread_mutex_lock(&philo->mutex_eat_check);
	philo->time_of_life = philo->handler->time_to_die + get_timestamp();
	pthread_mutex_unlock(&philo->mutex_eat_check);
	while (!check_individual_life(philo))
	{
		eat(philo);
		if (check_individual_life(philo))
			return (NULL);
		print_status(handler, philo->philo_id, "is sleeping");
		ft_usleep(handler->time_to_sleep);
		if (check_individual_life(philo))
			return (NULL);
		print_status(handler, philo->philo_id, "is thinking");
		if (check_individual_life(philo))
			return (NULL);
	}
	return (NULL);
}