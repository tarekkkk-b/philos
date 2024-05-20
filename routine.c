/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:39:25 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/05/20 19:45:01 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	*routine(void *p)
{
	t_philos	*philo;
	
	philo = (t_philos *)p;
	while (death(philo))
	{	
		if (philo->ID % 2 == 0 && philo->meals == 0)
		{
			thinking(philo);
			ft_usleep(philo->shared->time_to_eat/ 2, philo);
		}
		eating(philo);
		drop_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	eating(t_philos *philo)
{
	while (!take_forks(philo))
	{
		usleep(100);
		pthread_mutex_lock(&philo->shared->print);	
		death(philo);
		pthread_mutex_unlock(&philo->shared->print);	
	}
	philo->last_meal = get_current_time() - philo->shared->start;
	pthread_mutex_lock(&philo->shared->print);
	printf("\x1b[34m%lu %d is eating\n", 
		(get_current_time() - philo->shared->start), philo->ID);
	pthread_mutex_unlock(&philo->shared->print);
	ft_usleep(philo->shared->time_to_eat, philo);
	philo->meals++;
	pthread_mutex_lock(&philo->m_state);
	philo->state = 1;
	pthread_mutex_unlock(&philo->m_state);
}

void	sleeping(t_philos *philo)
{
	if (philo->state == 1)
	{	
		pthread_mutex_lock(&philo->shared->print);
		printf("\x1b[35m%lu %d is sleeping\n",
			(get_current_time() - philo->shared->start), philo->ID);
		pthread_mutex_unlock(&philo->shared->print);
		ft_usleep(philo->shared->time_to_sleep, philo);
		pthread_mutex_lock(&philo->m_state);
		philo->state = 2;
		pthread_mutex_unlock(&philo->m_state);
	}
	else
		return	;
}

void	thinking(t_philos *philo)
{
	pthread_mutex_lock(&philo->shared->print);
	printf("\x1b[32m%lu %d is thinking\n", 
		(get_current_time() - philo->shared->start), philo->ID);
	pthread_mutex_unlock(&philo->shared->print);
	pthread_mutex_lock(&philo->m_state);
	philo->state = 3;
	pthread_mutex_unlock(&philo->m_state);
}
