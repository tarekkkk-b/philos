/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:40:49 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/05/18 18:41:36 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_inp(int ac, char **av, t_shared *shared)
{
	if (ac < 5 || ac > 6)
		exit(1);
	shared->philos = atoi(av[1]);
	shared->time_to_die = atoi(av[2]);
	shared->time_to_eat = atoi(av[3]);
	shared->time_to_sleep = atoi(av[4]);
	shared->meals_ate = calloc(shared->philos, sizeof(int));
	if (ac == 6)
		shared->meals = atoi(av[5]);
	shared->philo = malloc(sizeof(t_philos *) * (shared->philos + 1));
	shared->philo[shared->philos] = NULL;
	int i = -1;
	while (++i < shared->philos)
	{
		shared->philo[i] = malloc(sizeof(t_philos));
		shared->philo[i]->ID = i + 1;
		shared->philo[i]->shared = shared;
	}
	shared->start = get_current_time();
}