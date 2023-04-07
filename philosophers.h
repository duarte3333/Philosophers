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
	int			last_time_eat;
	int			philo_id;
	int			nb_meals;
	t_handler	*handler;
}			t_philo;

typedef struct s_handler
{
	pthread_mutex_t		*forks;
	pthread_t			*threads;
	t_philo				*philosophers;
	int					time_to_eat;
	int					time_to_die;
	int					time_to_sleep;
	int					times_to_eat;
	int					num_philosophers;
	int					num_times_to_eat;
	int					time_to_start;
	pthread_t			my_mutex;

}		t_handler;

int			ft_atoi(const char *nptr);
int			ft_isdigit(int i);
void		*ft_calloc(size_t nmemb, size_t size);
void 		*routine(void *arg);
int			ft_forks_inicializer(t_handler *handler);
int			ft_threads_inicializer(t_handler *handler);
void		ft_usleep(int milisec);





#endif










	// struct s_handler	*handler;
	// int					last_meal;
	// int					sit;
	// int					eat_count;