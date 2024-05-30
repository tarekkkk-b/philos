/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:53:55 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/05/27 20:11:09 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *p)
{
	t_philo	*philo;

	philo = p;
	while (!(philo->shared->died) && (philo->meals != philo->shared->meals_req))
	{
		if (philo->id % 2 != 0 && philo->meals == 0)
			if (!ft_usleep(philo->shared->time_to_eat / 2, philo))
				return (drop_forks(philo), NULL);
		if (!eating(philo))
			return (drop_forks(philo), NULL);
		drop_forks(philo);
		if (!sleeping(philo))
			return (drop_forks(philo), NULL);
		if (!thinking(philo))
			return (drop_forks(philo), NULL);
	}
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
	if (checker(philo->shared->died, philo->shared->dead))
		return (FALSE);
	print(philo, &philo->shared->print, EATING, BLUE);
	if (!ft_usleep(philo->shared->time_to_eat, philo))
		return (FALSE);
	philo->meals++;
	return (TRUE);
}

int	sleeping(t_philo *philo)
{
	if (checker(philo->shared->died, philo->shared->dead))
		return (FALSE);
	print(philo, &philo->shared->print, SLEEPING, BLACK);
	if (!ft_usleep(philo->shared->time_to_sleep, philo))
		return (FALSE);
	return (TRUE);
}

int	thinking(t_philo *philo)
{
	if (checker(philo->shared->died, philo->shared->dead))
		return (FALSE);
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
		philo->shared->died = TRUE;
		usleep(600);
		print(philo, &philo->shared->print, DEATH, RED);
		return ((void)pthread_mutex_unlock(&philo->shared->check), FALSE);
	}
	return ((void)pthread_mutex_unlock(&philo->shared->check), TRUE);
}
