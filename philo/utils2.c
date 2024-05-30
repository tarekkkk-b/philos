/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:34:03 by tabadawi          #+#    #+#             */
/*   Updated: 2024/05/30 15:42:54 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checker(int value, pthread_mutex_t lock)
{
	int	status;

	status = FALSE;
	pthread_mutex_lock(&lock);
	if (value == TRUE)
		status = TRUE;
	pthread_mutex_unlock(&lock);
	return (status);
}

void	destroyer(t_shared *shared)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&shared->dead);
	pthread_mutex_destroy(&shared->last_meal_m);
	pthread_mutex_destroy(&shared->print);
	pthread_mutex_destroy(&shared->check);
	pthread_mutex_destroy(&shared->extra);
	while (++i < shared->philo_count)
		pthread_mutex_destroy(&shared->forks_m[i]);
}

void	freeer(t_philo **philo, t_shared *shared)
{
	int	i;
	int	j;

	i = -1;
	j = philo[0]->shared->philo_count;
	free (shared->forks);
	free (shared->forks_m);
	while (++i < j)
		free (philo[i]);
	free (philo);
}

void	err_free(t_shared *shared, t_philo **philo, int ind)
{
	int	i;

	i = -1;
	free(shared->forks);
	free(shared->forks_m);
	while (++i <= ind)
		free(philo[i]);
	free(philo);
}
