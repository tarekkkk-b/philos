/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:25:33 by tabadawi          #+#    #+#             */
/*   Updated: 2024/05/20 15:31:02 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_shared	*shared)
{
	int i = -1;
	while (++i < shared->philos)
	{
		pthread_create(&(shared->philo[i]->philo), NULL, routine,
			(void *)shared->philo[i]);
		// usleep(100);
	}
}

void	joiner(t_shared	*shared)
{
	int i = -1;
	while (++i < shared->philos)
		pthread_join(shared->philo[i]->philo, NULL);
}

int	main(int ac, char **av)
{
	t_shared	shared;

	pthread_mutex_init(&shared.print, NULL);
	check_inp(ac, av, &shared);
	create_threads(&shared);
	joiner(&shared);
}
