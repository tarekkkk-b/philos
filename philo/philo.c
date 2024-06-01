/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:59:11 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/05/31 22:29:11 by tarekkkk         ###   ########.fr       */
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
		return (-1);
	if (!initializer(&shared, ac, av))
		return (-1);
	philo = malloc(sizeof(t_philo *) * shared.philo_count);
	if (!philo_init(philo, &shared))
		return (-1);
	create_threads(philo);
	joiner(philo);
	destroyer(&shared);
	freeer(philo, &shared);
}
