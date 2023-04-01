#include "philosophers.h"

void	*ft_create_philos(t_handler *handler)
{
	int	i;

	i = 0;
	handler->philosophers = (t_philo *)malloc(sizeof(t_philo) * handler->num_philosophers);
	while (i < handler->num_philosophers)
	{
		handler->philosophers[i].philo_id = i;
		handler->philosophers[i].handler = handler;
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
			write (1, "Fork error", 12);
		i++;
	}
}

int	ft_threads_inicializer(t_handler *handler)
{
	int i;

	i = 0;
	handler->threads = (pthread_t *)ft_calloc(sizeof(pthread_t), handler->num_philosophers);
	if (!handler->threads)
		return (NULL);
	ft_create_philos(handler);
	while (i < (handler->num_philosophers))
	{
		//printf("oi %i\n", handler->philo_id);
		if (pthread_create(&(handler->threads[i]), NULL, routine, &(handler->philosophers[i])) != 0) 
			write (1, "Thread error", 12);
		i++;
		//printf("thread start %i\n", i);
	}
	i = 0;
	while (i < handler->num_philosophers)
	{
		if (pthread_join(handler->threads[i], NULL) != 0) 
			write (1, "Thread error", 12);
		i++;
		//printf("thread end %i\n", i);

	}
	return (1);
}