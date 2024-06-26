/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:02:26 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/06/01 20:06:01 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	right_fork(t_philo	*philo)
{
	pthread_mutex_lock(&philo->shared->forks_m[philo->id - 1]);
	if (philo->shared->forks[philo->id - 1])
	{
		pthread_mutex_lock(&philo->shared->extra);
		if (checker(philo->shared->died, philo->shared->dead))
			return ((void)pthread_mutex_unlock(&philo->shared->forks_m \
			[philo->id - 1]), pthread_mutex_unlock(&philo->shared->extra),
				FALSE);
		pthread_mutex_unlock(&philo->shared->extra);
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
	pthread_mutex_lock(&philo->shared->extra);
	if (checker(philo->shared->died, philo->shared->dead))
		return ((void)pthread_mutex_unlock(&philo->shared->forks_m \
		[id]), pthread_mutex_unlock(&philo->shared->extra), FALSE);
	pthread_mutex_unlock(&philo->shared->extra);
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
