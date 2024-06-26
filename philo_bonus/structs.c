/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:31 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/08 15:57:00 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	semaphores(t_shared *shared)
{
	int	i;

	i = -1;
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
	sem_unlink("/sem_pause");
	sem_unlink("/sem_check");
	sem_unlink("/sem_lock");
	shared->forks = sem_open("/sem_forks", O_CREAT, 0644, 0);
	while (++i < shared->philo_count)
		sem_post(shared->forks);
	shared->print = sem_open("/sem_print", O_CREAT, 0644, 1);
	shared->dead = sem_open("/sem_dead", O_CREAT, 0644, 0);
	shared->pause = sem_open("/sem_pause", O_CREAT, 0644, 0);
	shared->lock = sem_open("/sem_lock", O_CREAT, 0644, 1);
	if (shared->meals_req != -1)
	{
		shared->check = sem_open("/sem_check", O_CREAT, 0644, 1);
		sem_wait(shared->check);
	}
}

void	initializer(t_shared *shared, int ac, char **av)
{
	shared->philo_count = ft_atoi(av[1]);
	shared->time_to_die = ft_atoi(av[2]);
	shared->time_to_eat = ft_atoi(av[3]);
	shared->time_to_sleep = ft_atoi(av[4]);
	shared->pids = malloc(sizeof(pid_t) * shared->philo_count);
	if (ac == 6)
		shared->meals_req = ft_atoi(av[5]);
	else
		shared->meals_req = -1;
	semaphores(shared);
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
		philo[i]->death = 0;
		philo[i]->meals = 0;
		philo[i]->id = i + 1;
		philo[i]->shared = shared;
	}
}
