#include "philosophers.h"

/* Esta funcao reserva os garfos para o filosofo comer
O caso else corresponde ao caso do ultimo filosofo */
void lock_forks(t_philo *philo)
{
	int i;

	i = philo->philo_id;

	if (i < (philo->handler->num_philosophers - 1))
	{
		pthread_mutex_lock(&(philo->handler->forks[i]));
		pthread_mutex_lock(&(philo->handler->forks[(i + 1) % philo->handler->num_philosophers]));
	}
	else
	{
		pthread_mutex_lock(&(philo->handler->forks[(i + 1) % philo->handler->num_philosophers]));
		pthread_mutex_lock(&(philo->handler->forks[i]));
	}
	print_status(philo->handler, philo->philo_id, "has taken a fork");
	print_status(philo->handler, philo->philo_id, "has taken a fork");
}

/* Esta funcao deixa de reservar os garfos para o filosofo comer */
void unlock_forks(t_philo *philo)
{
	int i;

	i = philo->philo_id;
	if (i < (philo->handler->num_philosophers - 1))
	{
		pthread_mutex_unlock(&(philo->handler->forks[i]));
		pthread_mutex_unlock(&(philo->handler->forks[(i + 1) % philo->handler->num_philosophers]));
	}
	else
	{
		pthread_mutex_unlock(&(philo->handler->forks[(i + 1) % philo->handler->num_philosophers]));
		pthread_mutex_unlock(&(philo->handler->forks[i]));
	}
	print_status(philo->handler, philo->philo_id, "has taken a fork");
	print_status(philo->handler, philo->philo_id, "has taken a fork");
}

