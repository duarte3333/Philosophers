/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 17:45:55 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/03/25 11:33:11 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher t_philosopher;
typedef struct s_handler t_handler;

typedef struct s_philosopher
{
	__uint64_t		last_time_eat;
	int				philo_id;
	int				nb_meals;
	t_handler		*handler;
}			t_philo;

typedef struct s_handler
{
	pthread_mutex_t		*forks;
	pthread_mutex_t		mutex_printing;
	pthread_mutex_t		mutex_eat_check;
	pthread_t			*threads;
	pthread_t			aux_thread;
	t_philo				*philosophers;
	__uint64_t			time_to_eat;
	__uint64_t			time_to_die;
	__uint64_t			time_to_sleep;
	__uint64_t			times_to_eat;
	int					num_philosophers;
	int					num_times_to_eat;
	int					time_to_start;
	int					dead;
	int					all_eat;
	__uint64_t			begin_time;

}		t_handler;

//Parsing
int			ft_atoi(const char *nptr);
int			ft_isdigit(int i);
void		*ft_calloc(size_t nmemb, size_t size);

//Threads and mutexs inicializer
int			ft_forks_inicializer(t_handler *handler);
int			ft_threads_inicializer(t_handler *handler);

// The rotine
void 		*routine(void *arg);

//Functions for all threads
void		check_dead(t_handler *handler, t_philo *philo);
void 		check_all_eaten(t_handler *handler, t_philo *philo);

//Time
time_t		get_time(t_handler *handler);
time_t		get_timestamp(t_handler *handler);
void		ft_usleep(int milisec);
void 		print_status(t_handler *handler, int i, char *action);


#endif
