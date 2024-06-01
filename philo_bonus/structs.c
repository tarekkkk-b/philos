/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:31 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/02 01:07:08 by tarekkkk         ###   ########.fr       */
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
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
	shared->forks = sem_open("/sem_forks", O_CREAT, 0644, shared->philo_count / 2);
	shared->print = sem_open("/sem_print", O_CREAT, 0644, 1);
	shared->dead = sem_open("/sem_dead", O_CREAT, 0644, 1);
	if (ac == 6)
		shared->meals_req = ft_atoi(av[5]);
	else
		shared->meals_req = -1;
	shared->start = get_current_time();
}

void	philo_init(t_philo **philo, t_shared *shared)
{
	int	i;

	i = -1;
	while (++i < shared->philo_count)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->last_meal = 0;
		philo[i]->lf = 0;
		philo[i]->rf = 0;
		philo[i]->meals = 0;
		philo[i]->id = i + 1;
		philo[i]->shared = shared;
	}
}
