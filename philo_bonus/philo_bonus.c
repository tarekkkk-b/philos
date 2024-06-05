/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:38 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/05 13:21:38 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		if ((get_current_time() - philo->shared->start) - philo->last_meal >= philo->shared->time_to_die)
		{
			printing(philo, RED, DEATH, 1);
			sem_post(philo->shared->pause);
			// sem_wait(philo->shared->print);
			break ;
		}
	}
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
	sem_unlink("/sem_forks");
	sem_unlink("/sem_pause");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
}
