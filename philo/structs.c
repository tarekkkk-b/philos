/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:39:46 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/05/30 15:29:30 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_mutex(t_shared *shared)
{
	int	i;

	i = -1;
	pthread_mutex_init(&shared->dead, NULL);
	pthread_mutex_init(&shared->extra, NULL);
	pthread_mutex_init(&shared->print, NULL);
	pthread_mutex_init(&shared->last_meal_m, NULL);
	pthread_mutex_init(&shared->meal_m, NULL);
	pthread_mutex_init(&shared->check, NULL);
	while (++i < shared->philo_count)
		pthread_mutex_init(&shared->forks_m[i], NULL);
}

int	initializer(t_shared *shared, int ac, char **av)
{
	int	i;

	i = -1;
	shared->died = 0;
	shared->philo_count = ft_atoi(av[1]);
	shared->time_to_die = ft_atoi(av[2]);
	shared->time_to_eat = ft_atoi(av[3]);
	shared->time_to_sleep = ft_atoi(av[4]);
	shared->forks = malloc(sizeof(int) * shared->philo_count);
	if (!shared->forks)
		return (FALSE);
	shared->forks_m = malloc(sizeof(pthread_mutex_t) * shared->philo_count);
	if (!shared->forks)
		return (free(shared->forks), FALSE);
	while (++i < shared->philo_count)
		shared->forks[i] = 1;
	if (ac == 6)
		shared->meals_req = ft_atoi(av[5]);
	else
		shared->meals_req = -1;
	init_mutex(shared);
	shared->start = get_current_time();
	return (TRUE);
}

int	philo_init(t_philo **philo, t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->philo_count)
	{
		philo[i] = malloc(sizeof(t_philo));
		if (!philo[i])
			return (err_free(shared, philo, i), FALSE);
		philo[i]->rf = 0;
		philo[i]->lf = 0;
		philo[i]->meals = 0;
		philo[i]->last_meal = 0;
		philo[i]->id = i + 1;
		philo[i]->shared = shared;
		i++;
	}
	return (TRUE);
}
