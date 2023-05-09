/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:09:04 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/09 20:36:51 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Esta funcao liberta as memorias na heap e as threads e mutexs */
void	ft_destroy(t_handler *handler)
{
	int	i;

	i = 0;
	while (i < handler->num_philosophers)
	{
		if (pthread_mutex_destroy(&(handler->forks[i])) != 0)
			write (1, "Destroy error\n", 14);
		if (pthread_mutex_destroy(&(handler->philosophers[i].mutex_eat_check)) \
			!= 0)
			write (1, "Destroy error\n", 14);
		if (pthread_mutex_destroy(&(handler->philosophers[i].mutex_life)) != 0)
			write (1, "Destroy error\n", 14);
		i++;
	}
	free((void *)handler->philosophers);
	free((void *)handler->forks);
	free((void *)handler->threads);
}

/* Esta funcao comeca o projeto depois de fazer o parsing */
void	ft_loading(t_handler *handler)
{
	if (handler->num_philosophers == 1)
	{
		ft_usleep(handler->time_to_die);
		print_status(handler, 0, "died");
	}
	else
	{
		ft_mutexs_inicializer(handler);
		ft_threads_inicializer(handler);
		ft_destroy(handler);
	}
	free(handler);
}

int	main(int ac, char **av)
{
	t_handler	*handler;

	handler = (t_handler *)ft_calloc(sizeof(t_handler), 1);
	if (ac != 5 && ac != 6)
	{
		write(1, "Usage: [num_philos] [time to die]", 34);
		write(1, "[time to eat] [time to sleep] \n", 32);
		free(handler);
		return (0);
	}
	if (!parse(handler, av, ac))
		return (0);
	handler->num_philosophers = ft_atoi(av[1]);
	handler->time_to_die = ft_atoi(av[2]);
	handler->time_to_eat = ft_atoi(av[3]);
	handler->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		handler->num_times_to_eat = ft_atoi(av[5]);
	else
		handler->num_times_to_eat = INT_MAX;
	handler->begin_time = get_timestamp();
	ft_loading(handler);
}

/* 
void	all_prints(t_handler *handler)
{
	printf(" [num philo] %i philos\n", handler->num_philosophers);
	printf(" [time to die] %lu ms\n", handler->time_to_die);
	printf(" [time to eat] %lu ms\n", handler->time_to_eat);
	printf(" [time to sleep] %lu ms\n", handler->time_to_sleep);
	printf(" [num times to eat] %i meals\n\n", handler->num_times_to_eat);

}
 */