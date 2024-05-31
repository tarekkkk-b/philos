/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:31 by tabadawi          #+#    #+#             */
/*   Updated: 2024/05/31 15:09:29 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	initializer(t_shared *shared, int ac, char **av)
{
	int	i;

	i = -1;
	shared->philo_count = ft_atoi(av[1]);
	shared->time_to_die = ft_atoi(av[2]);
	shared->time_to_eat = ft_atoi(av[3]);
	shared->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		shared->meals_req = ft_atoi(av[5]);
	else
		shared->meals_req = -1;
	shared->start = get_current_time();
}
