/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:08 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/02 01:21:29 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


int	test(t_philo *philo)
{
	sem_wait(philo->shared->dead);
	sem_post(philo->shared->dead);
	return (1);
}
void	death(t_shared *shared, t_philo *philo)
{
	if ((get_current_time() - shared->start) - philo->last_meal >= shared->time_to_die)
	{
		sem_wait(philo->shared->dead);
		printf("%s[%ld] philo %d died\n", RED, get_current_time() - philo->shared->start, philo->id);
		exit(4);
	}
}

void	eating(t_philo *philo)
{
	philo->last_meal = get_current_time() - philo->shared->start;
	sem_wait(philo->shared->print);
	test(philo);
	printf("%s[%ld] philo %d is eating\n", BLUE, get_current_time() - philo->shared->start, philo->id);
	sem_post(philo->shared->print);
	test(philo);
	ft_usleep(philo->shared->time_to_eat, philo);
	philo->meals++;
}

void	sleeping(t_philo *philo)
{
	sem_wait(philo->shared->print);
	test(philo);
	printf("%s[%ld] philo %d is sleeping\n", BLACK, get_current_time() - philo->shared->start, philo->id);
	sem_post(philo->shared->forks);
	sem_post(philo->shared->print);
	test(philo);
	ft_usleep(philo->shared->time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	sem_wait(philo->shared->print);
	test(philo);
	printf("%s[%ld] philo %d is thinking\n", YELLOW, get_current_time() - philo->shared->start, philo->id);	
	sem_post(philo->shared->print);
}

void	routine(t_philo *philos)
{
	while (test(philos) && philos->meals != philos->shared->meals_req)
	{
		if (philos->id % 2 != 0 && philos->meals == 0)
			ft_usleep(philos->shared->time_to_eat / 2 , philos);
		test(philos);
		sem_wait(philos->shared->forks);
		printf("%s[%ld] philo %d has taken a fork\n", WHITE, get_current_time() - philos->shared->start, philos->id);	
		printf("%s[%ld] philo %d has taken a fork\n", WHITE, get_current_time() - philos->shared->start, philos->id);	
		test(philos);
		eating(philos);
		if (philos->meals == philos->shared->meals_req)
		{
			sem_post(philos->shared->forks);		
			exit (0);
		}
		test(philos);
		sleeping(philos);
		test(philos);
		thinking(philos);
	}
	exit (0);
}