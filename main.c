
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
	printf(" [num times to eat] %i meals\n", handler->num_times_to_eat);

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
}

//[time] 1681899453 
//[start] -1727726930 
//[end] -1727726730 
void	time_(int milisec)
{
	struct timeval	time_v;
	__uint64_t		start;
	__uint64_t		end;

	gettimeofday(&time_v, NULL);
	printf("[time] %i \n", time_v);

	start = (time_v.tv_sec * 1000) + (time_v.tv_usec / 1000);
	printf("[start] %i \n", start);
	end = start + milisec;
	printf("[end] %i \n", end);
	while (start < end)
	{
		gettimeofday(&time_v, NULL);
		start = (time_v.tv_sec * 1000) + (time_v.tv_usec / 1000);
		printf("[inside] %i \n", start);
		usleep(100);
	}
}

int main(int ac, char **av) 
{
	t_handler	*handler;

	handler = (t_handler *)malloc(sizeof(t_handler));
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
	pthread_mutex_init(&(handler->my_mutex), NULL);
	ft_forks_inicializer(handler);
	ft_threads_inicializer(handler);
	ft_destroy(handler);
	pthread_mutex_destroy(&(handler->my_mutex));
	free(handler->threads);
	free(handler->forks);
	free(handler);
}
   
