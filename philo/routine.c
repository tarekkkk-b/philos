/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:53:55 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/06/04 19:12:19 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *p)
{
	t_philo	*philo;

	philo = p;
	pthread_mutex_lock(&philo->shared->extra);
	while (!(philo->shared->died) && (philo->meals != philo->shared->meals_req))
	{
		pthread_mutex_unlock(&philo->shared->extra);
		if (philo->id % 2 != 0 && philo->meals == 0)
			if (!ft_usleep(philo->shared->time_to_eat / 2, philo))
				return (drop_forks(philo), NULL);
		if (!eating(philo))
			return (drop_forks(philo), NULL);
		if (philo->meals == philo->shared->meals_req)
			return (drop_forks(philo), NULL);
		if (!sleeping(philo))
			return (drop_forks(philo), NULL);
		if (!thinking(philo))
			return (drop_forks(philo), NULL);
		pthread_mutex_lock(&philo->shared->extra);
	}
	pthread_mutex_unlock(&philo->shared->extra);
	return (drop_forks(philo), NULL);
}

int	eating(t_philo *philo)
{
	while (!take_forks(philo))
	{
		usleep(100);
		if (!death(philo))
			return (FALSE);
	}
	philo->last_meal = (get_current_time() - philo->shared->start);
	pthread_mutex_lock(&philo->shared->extra);
	if (checker(philo->shared->died, philo->shared->dead))
		return ((void)pthread_mutex_unlock(&philo->shared->extra), FALSE);
	pthread_mutex_unlock(&philo->shared->extra);
	print(philo, &philo->shared->print, EATING, BLUE);
	if (!ft_usleep(philo->shared->time_to_eat, philo))
		return (FALSE);
	philo->meals++;
	return (TRUE);
}

int	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->extra);
	if (checker(philo->shared->died, philo->shared->dead))
		return ((void)pthread_mutex_unlock(&philo->shared->extra), FALSE);
	pthread_mutex_unlock(&philo->shared->extra);
	print(philo, &philo->shared->print, SLEEPING, BLACK);
	drop_forks(philo);
	if (!ft_usleep(philo->shared->time_to_sleep, philo))
		return (FALSE);
	return (TRUE);
}

int	thinking(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->extra);
	if (checker(philo->shared->died, philo->shared->dead))
		return ((void)pthread_mutex_unlock(&philo->shared->extra), FALSE);
	pthread_mutex_unlock(&philo->shared->extra);
	print(philo, &philo->shared->print, THINKING, YELLOW);
	return (TRUE);
}

int	death(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->check);
	if ((get_current_time() - philo->shared->start)
		- philo->last_meal >= philo->shared->time_to_die)
	{
		if (checker(philo->shared->died, philo->shared->dead))
			return ((void)pthread_mutex_unlock(&philo->shared->check), FALSE);
		pthread_mutex_lock(&philo->shared->extra);
		philo->shared->died = TRUE;
		pthread_mutex_unlock(&philo->shared->extra);
		usleep(600);
		print(philo, &philo->shared->print, DEATH, RED);
		return ((void)pthread_mutex_unlock(&philo->shared->check), FALSE);
	}
	return ((void)pthread_mutex_unlock(&philo->shared->check), TRUE);
}
