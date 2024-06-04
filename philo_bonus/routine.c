/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:08 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/04 10:53:18 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printing(t_philo *philo, char *clr, char *str, int flag)
{
	sem_wait(philo->shared->print);
	common_use(philo);
	if (!philo->death && !flag)
		printf("--%s%lu %d %s\n", clr, get_current_time() - philo->shared->start, philo->id, str);
	else if (flag)
	{
		common_use(philo);
		printf("%s%lu %d %s\n", clr, get_current_time() - philo->shared->start, philo->id, str);
		sem_post(philo->shared->forks);
		sem_post(philo->shared->forks);
		// sem_post(philo->shared->print);
		// exit(0);
	}
	sem_post(philo->shared->print);
	death(philo->shared, philo);
}

void	death(t_shared *shared, t_philo *philo)
{
	common_use(philo);
	if ((get_current_time() - shared->start) - philo->last_meal >= shared->time_to_die)
	{
		int i = 0;
		while (i < philo->shared->philo_count)
		{
			sem_post(philo->shared->dead);
			i++;
		}
		// sem_post(philo->shared->forks);
		// sem_post(philo->shared->forks);
		printing(philo, RED, DEATH, 1);
	}
}

void	eating(t_philo *philo)
{
	death(philo->shared, philo);
	common_use(philo);
	sem_wait(philo->shared->forks);
	printing(philo, WHITE, FORK, 0);
	sem_wait(philo->shared->forks);
	printing(philo, WHITE, FORK, 0);
	philo->last_meal = get_current_time() - philo->shared->start;
	printing(philo, BLUE, EATING, 0);
	ft_usleep(philo->shared->time_to_eat, philo);
	philo->meals++;
}

void	sleeping(t_philo *philo)
{
	death(philo->shared, philo);
	common_use(philo);
	printing(philo, BLACK, SLEEPING, 0);
	sem_post(philo->shared->forks);
	sem_post(philo->shared->forks);
	ft_usleep(philo->shared->time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	death(philo->shared, philo);
	common_use(philo);
	printing(philo, YELLOW, THINKING, 0);
}

void	routine(t_philo *philos)
{
	while (!philos->death && philos->meals != philos->shared->meals_req)
	{
		if (philos->id % 2 != 0 && philos->meals == 0)
			ft_usleep(philos->shared->time_to_eat / 2 , philos);
		eating(philos);
		if (philos->meals == philos->shared->meals_req)
		{
			sem_post(philos->shared->forks);	
			sem_post(philos->shared->forks);	
			sem_post(philos->shared->dead);
			// exit (0);
		}
		// common_use(philos);
		sleeping(philos);
		thinking(philos);
	}
}
