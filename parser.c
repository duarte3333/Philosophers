/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsa-mora <dsa-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:14:47 by dsa-mora          #+#    #+#             */
/*   Updated: 2023/05/09 20:34:43 by dsa-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_parsing(char **av)
{
	int	i;
	int	j;

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

int	ft_check_limits(char *str)
{
	int			i;
	long long	num;
	int			signal;

	signal = 1;
	i = 0;
	if (str[0] == '-')
	{
		signal *= -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	if (ft_strlen(str + i) > 10)
		return (0);
	num = 0;
	i--;
	while (str[++i])
		num = num * 10 + str[i] - '0';
	if ((num * signal) > INT_MAX || (num * signal) < INT_MIN)
		return (0);
	return (1);
}

int	parse(t_handler *handler, char **av, int ac)
{
	int	i;

	if (!ft_parsing(av))
	{
		write(1, "Parsing error\n", 15);
		free(handler);
		return (0);
	}
	i = 1;
	while (i < ac)
	{
		if (!ft_check_limits(av[i]))
		{
			write(1, "One argument is too big\n", 25);
			free(handler);
			return (0);
		}
		i++;
	}
	return (1);
}
