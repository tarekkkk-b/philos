/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:38 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/03 15:22:32 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	sem_wait(philo->shared->dead);
	philo->death = 1;
	// exit(1);
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
			pthread_create(&philos[i]->monitor, NULL, monitor, (void *)philos[i]);
			routine(philos[i]);
		}
	}
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
		waitpid(shared.pids[i], 0, 0);
	i = -1;
	while (++i < shared.philo_count)
		pthread_join(philos[i]->monitor, NULL);
	sem_close(shared.forks);
	sem_close(shared.print);
	sem_close(shared.dead);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
}
