/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:08 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/02 21:52:30 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


// int	test(t_philo *philo)
// {
// 	sem_wait(philo->shared->dead);
// 	sem_post(philo->shared->dead);
// 	return (1);
// }



int	death(t_shared *shared, t_philo *philo)
{
	// printf("hi\n");
	if ((get_current_time() - shared->start) - philo->last_meal >= shared->time_to_die)
	{
		int i = 0;
		while (i < philo->shared->philo_count)
		{
			sem_post(philo->shared->dead);
			i++;
		}
		// sem_wait(philo->shared->dead);
		sem_wait(philo->shared->print);
		sem_post(philo->shared->forks);
		sem_post(philo->shared->forks);
		printf("%s[%ld] philo %d died\n", RED, get_current_time() - philo->shared->start, philo->id);
		sem_post(philo->shared->print);
		// exit(4);
		return (1);
	}
	return (0);
}

void	eating(t_philo *philo)
{
	// if (death(philo->shared, philo))
	// 	exit(1);
	philo->last_meal = get_current_time() - philo->shared->start;
	death(philo->shared, philo);
	if (philo->death)
	{
		sem_post(philo->shared->forks);	
		sem_post(philo->shared->forks);
		exit(0);
	}
	// test(philo);
	sem_wait(philo->shared->print);
	printf("%s[%ld] philo %d is eating\n", BLUE, get_current_time() - philo->shared->start, philo->id);
	sem_post(philo->shared->print);
	// test(philo);
	death(philo->shared, philo);
	if (philo->death)
	{
		sem_post(philo->shared->forks);	
		sem_post(philo->shared->forks);
		exit(0);
	}
	ft_usleep(philo->shared->time_to_eat, philo);
	philo->meals++;
}

void	sleeping(t_philo *philo)
{
	// if (death(philo->shared, philo))
	// 	exit(1);
	// test(philo);
	death(philo->shared, philo);
	if (philo->death)
	{
		sem_post(philo->shared->forks);	
		sem_post(philo->shared->forks);
		exit(0);
	}
	sem_wait(philo->shared->print);
	printf("%s[%ld] philo %d is sleeping\n", BLACK, get_current_time() - philo->shared->start, philo->id);
	sem_post(philo->shared->print);
	sem_post(philo->shared->forks);
	sem_post(philo->shared->forks);
	// test(philo);
	death(philo->shared, philo);
	if (philo->death)
	{
		sem_post(philo->shared->forks);	
		sem_post(philo->shared->forks);
		exit(0);
	}
	ft_usleep(philo->shared->time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	death(philo->shared, philo);
	// test(philo);
	if (philo->death)
	{
		sem_post(philo->shared->forks);	
		sem_post(philo->shared->forks);
		exit(0);
	}
	sem_wait(philo->shared->print);
	printf("%s[%ld] philo %d is thinking\n", YELLOW, get_current_time() - philo->shared->start, philo->id);	
	sem_post(philo->shared->print);
}

void	routine(t_philo *philos)
{
	while (!philos->death && philos->meals != philos->shared->meals_req)
	{
		if (philos->id % 2 != 0 && philos->meals == 0)
			ft_usleep(philos->shared->time_to_eat / 2 , philos);
		// test(philos);
		
		if (philos->death)
		{
			sem_post(philos->shared->forks);	
			sem_post(philos->shared->forks);	
			exit(0);
		}
		sem_wait(philos->shared->forks);
		printf("%s[%ld] philo %d has taken a fork\n", WHITE, get_current_time() - philos->shared->start, philos->id);	
		sem_wait(philos->shared->forks);
		printf("%s[%ld] philo %d has taken a fork\n", WHITE, get_current_time() - philos->shared->start, philos->id);	
		// test(philos);
		if (philos->death)
		{
			sem_post(philos->shared->forks);	
			sem_post(philos->shared->forks);	
			exit(0);
		}
		eating(philos);
		if (philos->meals == philos->shared->meals_req)
		{
			sem_post(philos->shared->forks);	
			sem_post(philos->shared->forks);	
			exit (0);
		}
		// test(philos);
		if (philos->death)
		{
			sem_post(philos->shared->forks);	
			sem_post(philos->shared->forks);	
			exit(0);
		}
		sleeping(philos);
		if (philos->death)
		{
			sem_post(philos->shared->forks);	
			sem_post(philos->shared->forks);
			exit(0);
		}
		// test(philos);
		thinking(philos);
	}
	exit (0);
}
