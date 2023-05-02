#include "philosophers.h"

int	ft_parsing(char **av)
{
	int i;
	int j;

	i = 0;
	while (av[++i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
	}
	return (1);

}

void	all_prints(t_handler *handler)
{
	printf(" [num philo] %i philos\n", handler->num_philosophers);
	printf(" [time to die] %i ms\n", handler->time_to_die);
	printf(" [time to eat] %i ms\n", handler->time_to_eat);
	printf(" [time to sleep] %i ms\n", handler->time_to_sleep);
	printf(" [num times to eat] %i meals\n\n", handler->num_times_to_eat);

}

void	ft_destroy(t_handler *handler)
{
	int i;

	i = 0;
	while (i < handler->num_philosophers)
	{
		if (pthread_mutex_destroy(&(handler->forks[i])) != 0) 
			write (1, "Destroy error", 12);
		i++;
	}
	if (pthread_mutex_destroy(&handler->mutex_printing) != 0)
		write (1, "Destroy error", 12);
	if (pthread_mutex_destroy(&handler->mutex_eat_check) != 0)
		write (1, "Destroy error", 12);
}
 
int main(int ac, char **av) 
{
	t_handler	*handler;

	handler = (t_handler *)ft_calloc(sizeof(t_handler), 1);
    if (ac != 5 && ac != 6) {
		write(1, "Usage: [num_philos] [time to die] [time to eat] [time to sleep] \n", 66);
        exit(0);
    }
	if (!ft_parsing(av))
	{
		write(1, "Parsing error\n", 15);
		return (0) ;
	}
    handler->num_philosophers = ft_atoi(av[1]);
    handler->time_to_die = ft_atoi(av[2]);
    handler->time_to_eat = ft_atoi(av[3]);
    handler->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		handler->num_times_to_eat = ft_atoi(av[5]);
	else
		handler->num_times_to_eat = INT_MAX;
	all_prints(handler);
	ft_forks_inicializer(handler);
	ft_threads_inicializer(handler);
	ft_destroy(handler);
	free(handler->threads);
	free(handler->forks);
	free(handler);
}
   
