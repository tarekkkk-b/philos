/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:39:25 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/05/19 21:17:48 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philos	*philo)
{
	if (!philo->rf)
		if (philo->avail)
		{
			philo->rf = 1;
			philo->avail = 0;
		}
	if (!philo->lf)
	{
		if (philo->ID == 1)
		{
			if (philo->shared->philo[philo->shared->philos - 1]->avail)
			{
				philo->lf = 1;
				philo->shared->philo[philo->shared->philos - 1]->avail = 0;
			}
		}
		else
			if (philo->shared->philo[philo->ID - 2]->avail)
			{
				philo->lf = 1;
				philo->shared->philo[philo->ID - 2]->avail = 0;
			}
	}
	if (philo->rf && philo->lf)
		return (1);
	return (0);
}

void	drop_forks(t_philos	*philo)
{
	if (philo->state == 1)
	{
		philo->rf = 0;
		philo->lf = 0;
		philo->avail = 1;
		if (philo->ID == 1)
			philo->shared->philo[philo->shared->philos - 1]->avail = 1;
		else
			philo->shared->philo[philo->ID - 2]->avail = 1;
		return	;	
	}
	return	;
}

void	*routine(void *philo)
{
	while (death(philo))
	{	
		eating(philo);
		drop_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	eating(t_philos *philo)
{
	if (!take_forks(philo))
		return	;
	philo->last_meal = get_current_time() - philo->shared->start;
	pthread_mutex_lock(&philo->shared->print);
	printf("\x1b[34m[%lu] philo %d: is eating\n", 
		(get_current_time() - philo->shared->start), philo->ID);
	pthread_mutex_unlock(&philo->shared->print);
	ft_usleep(philo->shared->time_to_eat, philo);
	philo->meals++;
	philo->state = 1;
}

void	sleeping(t_philos *philo)
{
	if (philo->state != 2)
		return	;
	pthread_mutex_lock(&philo->shared->print);
	printf("\x1b[35m[%lu] philo %d: is sleeping\n",
		(get_current_time() - philo->shared->start), philo->ID);
	pthread_mutex_unlock(&philo->shared->print);
	ft_usleep(philo->shared->time_to_sleep, philo);
	philo->state = 2;
}

void	thinking(t_philos *philo)
{
	pthread_mutex_lock(&philo->shared->print);
	printf("\x1b[32m[%lu] philo %d: is thinking\n", 
		(get_current_time() - philo->shared->start), philo->ID);
	pthread_mutex_unlock(&philo->shared->print);
	philo->state = 3;
}
