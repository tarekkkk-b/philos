/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:59:11 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/05/25 21:24:50 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_philo **philo)
{
	int	i;

	i = -1;
	while (++i < philo[0]->shared->philo_count)
		pthread_create(&philo[i]->philo, NULL, routine, (void *)philo[i]);
}

void	joiner(t_philo	**philo)
{
	int	i;

	i = -1;
	while (++i < philo[0]->shared->philo_count)
		pthread_join(philo[i]->philo, NULL);
}

int	main(int ac, char **av)
{
	t_shared	shared;
	t_philo		**philo;

	if (!check_args(ac, av))
		return (0);
	if (!initializer(&shared, ac, av))
		return (FALSE);
	philo = malloc(sizeof(t_philo *) * shared.philo_count);
	if (!philo_init(philo, &shared))
		return (FALSE);
	create_threads(philo);
	joiner(philo);
	destroyer(&shared);
	freeer(philo, &shared);
}
