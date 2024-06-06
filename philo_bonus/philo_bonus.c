/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:38 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/06 17:49:28 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *p)
{
	t_philo	*philo;
	int	i;

	philo = (t_philo *)p;
	while (1)
	{
		if ((get_current_time() - philo->shared->start) - philo->last_meal >= philo->shared->time_to_die)
		{
			printing(philo, RED, DEATH, 1);
			i = -1;
			while (++i < philo->shared->philo_count)
				sem_post(philo->shared->pause);
			break ;
		}
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
	pid_t	x = -1;

	i = -1;
	while (++i < shared->philo_count)
	{
		x = fork();
		if (x > 0)
			shared->pids[i] = x;
		else if (!x)
		{
			pthread_create(&philos[i]->monitor, NULL,
				monitor, (void *)philos[i]);
			routine(philos[i]);
		}
	}
	if (shared->meals_req != -1)
		pthread_create(&shared->meal_checking, NULL, meal_checker, (void *)shared);
	sem_wait(shared->pause);
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
	int i = -1;
	while (++i < shared.philo_count)
		kill(shared.pids[i], SIGKILL);
	i = -1;
	while (++i < shared.philo_count)
		pthread_join(philos[i]->monitor, NULL);
	sem_close(shared.forks);
	sem_close(shared.print);
	sem_close(shared.dead);
	sem_close(shared.pause);
	if (sem_post(shared.check))
		sem_close(shared.check);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_pause");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
	sem_unlink("/sem_check");
	return (0);
}
