/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:36:39 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/09 20:33:09 by dsa-mora         ###   ########.fr       */
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

typedef struct s_philosopher	t_philosopher;
typedef struct s_handler		t_handler;

typedef struct s_philosopher
{
	__uint64_t			last_time_eat;
	int					philo_id;
	int					nb_meals;
	__int64_t			time_of_life;
	int					dead;
	pthread_mutex_t		mutex_eat_check;
	pthread_mutex_t		mutex_life;
	t_handler			*handler;
}			t_philo;

typedef struct s_handler
{
	pthread_mutex_t		*forks;
	pthread_t			*threads;
	pthread_t			aux_thread;
	t_philo				*philosophers;
	__uint64_t			time_to_eat;
	__uint64_t			time_to_die;
	__uint64_t			time_to_sleep;
	__uint64_t			times_to_eat;
	int					num_philosophers;
	int					num_times_to_eat;
	__uint64_t			time_to_start;
	int					dead;
	__uint64_t			begin_time;

}		t_handler;

//Parsing
size_t		ft_strlen(const char *str);
int			ft_atoi(const char *nptr);
int			ft_isdigit(int i);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_parsing(char **av);
int			ft_check_limits(char *str);
int			parse(t_handler *handler, char **av, int ac);

//Threads and mutexs inicializer
void		ft_mutexs_inicializer(t_handler *handler);
void		ft_threads_inicializer(t_handler *handler);

// The rotine
void		*routine(void *arg);
void		eat(t_philo *philo);
void		lock_forks(t_philo *philo);
void		unlock_forks(t_philo *philo);

//The aux_rotine
void		*supervisor(void *arg);
int			check_life(t_handler *handler, int i);
int			check_all_eaten(t_handler *handler, t_philo *philo, int j);

//Time
time_t		get_time(t_handler *handler);
time_t		get_timestamp(void);
void		ft_usleep(int milisec);
void		print_status(t_handler *handler, int i, char *action);

#endif
