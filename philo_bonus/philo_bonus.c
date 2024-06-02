/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:38 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/02 15:40:20 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	create_processes(t_philo **philos, t_shared *shared)
{
	int	i;
	pid_t	x = -1;

	i = -1;
	while (++i < shared->philo_count)
	{
		x = fork();
		if (x > 0)
			philos[i]->philo = x;
		else if (!x)
			routine(philos[i]);
	}
}

int	main(int ac, char **av)
{
	t_shared	shared;
	t_philo		**philos;
	int			s;
	int			q = 0;
	pid_t		tmp;

	if (!check_args(ac, av))
		return (-1);
	initializer(&shared, ac, av);
	philos = malloc(sizeof(t_philo *) * shared.philo_count);
	philo_init(philos, &shared);
	create_processes(philos, &shared);
	int i = -1;
	while (++i < shared.philo_count)
	{
		tmp = wait(&s);
		if (WEXITSTATUS(s) == 4)
		{
			while (q < shared.philo_count)
			{
				if (philos[q]->philo != tmp)
					kill(philos[q]->philo, SIGQUIT);
				q++;
			}
			break ;
		}
	}
	sem_close(shared.forks);
	sem_close(shared.print);
	sem_close(shared.dead);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
}
