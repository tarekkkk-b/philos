/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:39:25 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/05/18 21:46:56 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	while (1)
	{	
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	eating(t_philos *philo)
{
	philo->last_meal = get_current_time() - philo->shared->start;
	pthread_mutex_lock(&philo->shared->print);
	printf("\x1b[34m[%lu] philo %d: ate\n", 
		(get_current_time() - philo->shared->start), philo->ID);
	pthread_mutex_unlock(&philo->shared->print);
	ft_usleep(philo->shared->time_to_eat, philo);
	
}

void	sleeping(t_philos *philo)
{
	pthread_mutex_lock(&philo->shared->print);
	printf("\x1b[33m[%lu] philo %d: slept\n",
		(get_current_time() - philo->shared->start), philo->ID);
	pthread_mutex_unlock(&philo->shared->print);
	ft_usleep(philo->shared->time_to_sleep, philo);
}

void	thinking(t_philos *philo)
{
	pthread_mutex_lock(&philo->shared->print);
	printf("\x1b[32m[%lu] philo %d: thought\n", 
		(get_current_time() - philo->shared->start), philo->ID);
	pthread_mutex_unlock(&philo->shared->print);
}
