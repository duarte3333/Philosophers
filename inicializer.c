/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inicializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:42:24 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/09 14:42:39 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_create_philos(t_handler *handler)
{
	int	i;

	i = 0;
	handler->philosophers = (t_philo *)ft_calloc(sizeof(t_philo), \
		handler->num_philosophers);
	while (i < handler->num_philosophers)
	{
		handler->philosophers[i].philo_id = i;
		handler->philosophers[i].handler = handler;
		if (pthread_mutex_init(&(handler->philosophers[i].mutex_eat_check), \
			NULL) != 0)
			write (1, "Mutex error", 13);
		if (pthread_mutex_init(&(handler->philosophers[i].mutex_life), \
			NULL) != 0)
			write (1, "Mutex error", 13);
		i++;
	}
}

void	create_threads(t_handler *handler)
{
	int	i;

	i = 0;
	handler->begin_time = get_timestamp();
	while (i < (handler->num_philosophers))
	{
		if (pthread_create(&(handler->threads[i]), NULL, routine, \
			&(handler->philosophers[i])) != 0)
			write(1, "Thread error\n", 13);
		i++;
	}
	if (pthread_create(&(handler->aux_thread), NULL, supervisor, handler) != 0)
		write(1, "Thread error\n", 13);
}

void	join_threads(t_handler *handler)
{
	int	i;

	i = 0;
	while (i < handler->num_philosophers)
	{
		if (pthread_join(handler->threads[i], NULL) != 0)
			write (1, "Thread error\n", 13);
		i++;
	}
	if (pthread_join(handler->aux_thread, NULL) != 0)
		write(1, "Thread error\n", 13);
}

void	ft_mutexs_inicializer(t_handler *handler)
{
	int	i;

	i = 0;
	handler->forks = (pthread_mutex_t *)ft_calloc(sizeof(pthread_mutex_t), \
		handler->num_philosophers);
	while (i < handler->num_philosophers)
	{
		if (pthread_mutex_init(&(handler->forks[i]), NULL) != 0)
			write (1, "Mutex error", 13);
		i++;
	}
}

void	ft_threads_inicializer(t_handler *handler)
{
	handler->threads = (pthread_t *)ft_calloc(sizeof(pthread_t), \
		handler->num_philosophers);
	ft_create_philos(handler);
	create_threads(handler);
	join_threads(handler);
}
