/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:38 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/08 15:40:10 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *p)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)p;
	while (1)
	{
		sem_wait(philo->shared->lock);
		if ((get_current_time() - philo->shared->start) - philo->last_meal
			>= philo->shared->time_to_die)
		{
			printing(philo, RED, DEATH, 1);
			i = -1;
			while (++i < (philo->shared->philo_count))
			{
				sem_post(philo->shared->pause);
				if (philo->shared->meals_req != -1)
					sem_post(philo->shared->check);
			}
			sem_post(philo->shared->lock);
			break ;
		}
		sem_post(philo->shared->lock);
	}
	return (NULL);
}

void	*meal_checker(void *s)
{
	t_shared	*shared;
	int			i;

	i = -1;
	shared = (t_shared *)s;
	while (++i < shared->philo_count)
		sem_wait(shared->check);
	i = -1;
	while (++i < shared->philo_count)
		sem_post(shared->pause);
	return (NULL);
}

void	create_processes(t_philo **philos, t_shared *shared)
{
	int	i;

	i = -1;
	if (shared->meals_req != -1)
		pthread_create(&shared->meal_checking, NULL,
			meal_checker, (void *)shared);
	while (++i < shared->philo_count)
	{
		shared->pids[i] = fork();
		if (shared->pids[i] < 0)
			exit(0);
		else if (!shared->pids[i])
		{
			pthread_create(&philos[i]->monitor, NULL,
				monitor, (void *)philos[i]);
			routine(philos[i]);
			pthread_join(philos[i]->monitor, NULL);
			close_semaphores(shared);
		}
	}
	sem_wait(shared->pause);
}

void	ending(t_shared *shared, t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < shared->philo_count)
	{
		free(philo[i]);
		kill(shared->pids[i], SIGKILL);
	}
	if (shared->meals_req != -1)
		pthread_join(shared->meal_checking, NULL);
	free(philo);
	free (shared->pids);
	close_semaphores(shared);
}

int	main(int ac, char **av)
{
	t_shared	shared;
	t_philo		**philos;

	if (!check_args(ac, av))
		return (-1);
	initializer(&shared, ac, av);
	philos = malloc(sizeof(t_philo *) * shared.philo_count);
	philo_init(philos, &shared);
	create_processes(philos, &shared);
	ending(&shared, philos);
}
