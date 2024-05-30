/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:02:26 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/05/30 13:21:12 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	right_fork(t_philo	*philo)
{
	pthread_mutex_lock(&philo->shared->forks_m[philo->id - 1]);
	if (philo->shared->forks[philo->id - 1])
	{
		if (checker(philo->shared->died, philo->shared->dead))
			return ((void)pthread_mutex_unlock(&philo->shared->forks_m \
			[philo->id - 1]), FALSE);
		print(philo, &philo->shared->print, FORK, WHITE);
		philo->shared->forks[philo->id - 1] = 0;
		return ((void)pthread_mutex_unlock(&philo->shared->forks_m \
		[philo->id - 1]), TRUE);
	}
	return ((void)pthread_mutex_unlock(&philo->shared->forks_m \
	[philo->id - 1]), FALSE);
}

static int	left_fork2(t_philo *philo, int id)
{
	if (checker(philo->shared->died, philo->shared->dead))
		return ((void)pthread_mutex_unlock(&philo->shared->forks_m \
		[id]), FALSE);
	print(philo, &philo->shared->print, FORK, WHITE);
	philo->shared->forks[id] = 0;
	return ((void)pthread_mutex_unlock(&philo->shared->forks_m[id]), TRUE);
}

static int	left_fork(t_philo *philo)
{
	if (philo->id == 1)
	{
		pthread_mutex_lock(&philo->shared->forks_m \
		[philo->shared->philo_count - 1]);
		if (philo->shared->forks[philo->shared->philo_count - 1])
			return (left_fork2(philo, philo->shared->philo_count - 1));
		pthread_mutex_unlock(&philo->shared->forks_m \
		[philo->shared->philo_count - 1]);
	}
	else
	{
		pthread_mutex_lock(&philo->shared->forks_m[philo->id - 2]);
		if (philo->shared->forks[philo->id - 2])
			return (left_fork2(philo, philo->id - 2));
		return ((void)pthread_mutex_unlock(&philo->shared->forks_m \
		[philo->id - 2]), FALSE);
	}
	return (FALSE);
}

int	take_forks(t_philo *philo)
{
	if (!philo->rf)
		if (right_fork(philo))
			philo->rf = 1;
	if (!philo->lf)
		if (left_fork(philo))
			philo->lf = 1;
	if (philo->lf && philo->rf)
		return (TRUE);
	return (FALSE);
}

void	drop_forks(t_philo *philo)
{
	if (philo->rf)
	{
		philo->rf = 0;
		pthread_mutex_lock(&philo->shared->forks_m[philo->id - 1]);
		philo->shared->forks[philo->id - 1] = 1;
		pthread_mutex_unlock(&philo->shared->forks_m[philo->id - 1]);
	}
	if (philo->lf)
	{
		philo->lf = 0;
		if (philo->id == 1)
		{
			pthread_mutex_lock(&philo->shared->forks_m \
			[philo->shared->philo_count - 1]);
			philo->shared->forks[philo->shared->philo_count - 1] = 1;
			pthread_mutex_unlock(&philo->shared->forks_m \
			[philo->shared->philo_count - 1]);
		}
		else
		{
			pthread_mutex_lock(&philo->shared->forks_m[philo->id - 2]);
			philo->shared->forks[philo->id - 2] = 1;
			pthread_mutex_unlock(&philo->shared->forks_m[philo->id - 2]);
		}
	}
}
