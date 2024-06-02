/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:08 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/02 22:45:01 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


// int	test(t_philo *philo)
// {
// 	sem_wait(philo->shared->dead);
// 	sem_post(philo->shared->dead);
// 	return (1);
// }

void	printing(t_philo *philo, char *clr, char *str, int flag)
{
	sem_wait(philo->shared->print);
	if (!philo->death)
		printf("%s%lu %d %s\n", clr, get_current_time() - philo->shared->start, philo->id, str);
	else if (flag)
		printf("%s%lu %d %s\n", clr, get_current_time() - philo->shared->start, philo->id, str);
	sem_post(philo->shared->print);
}

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
		// sem_wait(philo->shared->print);
		sem_post(philo->shared->forks);
		sem_post(philo->shared->forks);
		printing(philo, RED, DEATH, 1);
		// printf("%s[%ld] philo %d died\n", RED, get_current_time() - philo->shared->start, philo->id);
		// sem_wait(philo->shared->print);
		// sem_post(philo->shared->print);
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
	// sem_wait(philo->shared->print);
	printing(philo, BLUE, EATING, 0);
	// printf("%s[%ld] philo %d is eating\n", BLUE, get_current_time() - philo->shared->start, philo->id);
	// sem_post(philo->shared->print);
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
	// sem_wait(philo->shared->print);
	printing(philo, BLACK, SLEEPING, 0);
	// printf("%s[%ld] philo %d is sleeping\n", BLACK, get_current_time() - philo->shared->start, philo->id);
	// sem_post(philo->shared->print);
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
	// sem_wait(philo->shared->print);
	printing(philo, YELLOW, THINKING, 0);
	// printf("%s[%ld] philo %d is thinking\n", YELLOW, get_current_time() - philo->shared->start, philo->id);	
	// sem_post(philo->shared->print);
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
		printing(philos, WHITE, FORK, 0);
		sem_wait(philos->shared->forks);
		printing(philos, WHITE, FORK, 0);
		// printf("%s[%ld] philo %d has taken a fork\n", WHITE, get_current_time() - philos->shared->start, philos->id);	
		// printf("%s[%ld] philo %d has taken a fork\n", WHITE, get_current_time() - philos->shared->start, philos->id);	
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
