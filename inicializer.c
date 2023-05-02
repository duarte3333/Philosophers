#include "philosophers.h"

void	*ft_create_philos(t_handler *handler)
{
	int	i;

	i = 0;
	handler->philosophers = (t_philo *)ft_calloc(sizeof(t_philo), handler->num_philosophers);
	while (i < handler->num_philosophers)
	{
		handler->philosophers[i].philo_id = i;
		handler->philosophers[i].nb_meals = handler->num_times_to_eat;
		handler->philosophers[i].handler = handler;
		handler->philosophers[i].last_time_eat = 0;
		i++;
	}
}

int	ft_forks_inicializer(t_handler *handler)
{
	int i;

	i = 0;
	handler->forks = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t), handler->num_philosophers);
	while (i < handler->num_philosophers)
	{
		if (pthread_mutex_init(&(handler->forks[i]), NULL) != 0) 
			write (1, "Mutex error", 13);
		i++;
	}
	if (pthread_mutex_init(&handler->mutex_printing, NULL) != 0)
			write (1, "Mutex error", 13);
	if (pthread_mutex_init(&handler->mutex_eat_check, NULL) != 0)
			write (1, "Mutex error", 13);


}

int	ft_threads_inicializer(t_handler *handler)
{
	int i;
	struct timeval temp_time;

	i = 0;
	handler->threads = (pthread_t *)ft_calloc(sizeof(pthread_t), handler->num_philosophers);
	if (!handler->threads)
		return (NULL);
	ft_create_philos(handler);
	handler->begin_time = get_timestamp(handler);
	while (i < (handler->num_philosophers))
	{
		if (pthread_create(&(handler->threads[i]), NULL, routine, &(handler->philosophers[i])) != 0) 
			write (1, "Thread error\n", 13);
		handler->philosophers->last_time_eat = get_timestamp(handler);
		i++;
	}
	check_dead(handler, handler->philosophers);
	i = 0;
	while (i < handler->num_philosophers)
	{
		if (pthread_join(handler->threads[i], NULL) != 0) 
			write (1, "Thread error\n", 13);
		i++;
	}
	return (1);
}