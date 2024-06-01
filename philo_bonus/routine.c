/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:08 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/01 15:28:38 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *philo)
{
	sem_wait(philo->shared->print);
	printf("%s[%ld] philo %d is eating\n", BLUE, get_current_time() - philo->shared->start, philo->id);
	sem_post(philo->shared->print);
	ft_usleep(philo->shared->time_to_eat);
	philo->meals++;
}

void	sleeping(t_philo *philo)
{
	sem_post(philo->shared->forks);
	sem_wait(philo->shared->print);
	printf("%s[%ld] philo %d is sleeping\n", BLACK, get_current_time() - philo->shared->start, philo->id);
	sem_post(philo->shared->print);
	ft_usleep(philo->shared->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	sem_wait(philo->shared->print);
	printf("%s[%ld] philo %d is thinking\n", YELLOW, get_current_time() - philo->shared->start, philo->id);	
	sem_post(philo->shared->print);
}

void	routine(t_philo *philos)
{
	while (philos->meals != philos->shared->meals_req)
	{
		if (philos->id % 2 != 0 && philos->meals == 0)
			ft_usleep(philos->shared->time_to_eat / 2);
		sem_wait(philos->shared->forks);
		eating(philos);
		if (philos->meals == philos->shared->meals_req)
		{
			sem_post(philos->shared->forks);		
			exit (0);
		}
		sleeping(philos);
		thinking(philos);
	}
	exit (0);
}