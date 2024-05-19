/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:40:49 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/05/19 19:48:01 by tarekkkk         ###   ########.fr       */
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
	if (ac == 6)
		shared->meals = atoi(av[5]);
	shared->philo = malloc(sizeof(t_philos *) * (shared->philos + 1));
	shared->philo[shared->philos] = NULL;
	int i = -1;
	while (++i < shared->philos)
	{
		shared->philo[i] = malloc(sizeof(t_philos));
		shared->philo[i]->ID = i + 1;
		shared->philo[i]->meals = 0;
		shared->philo[i]->last_meal = 0;
		shared->philo[i]->rf = 0;
		shared->philo[i]->lf = 0;
		shared->philo[i]->state = 0;
		shared->philo[i]->avail = 1;
		shared->philo[i]->shared = shared;
		pthread_mutex_init(&shared->philo[i]->fork, NULL);
	}
	shared->start = get_current_time();
}
