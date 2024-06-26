/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:16:08 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/08 15:53:04 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	printing(t_philo *philo, char *clr, char *str, int flag)
{
	if (philo->shared->meals_req != -1
		&& (philo->meals >= philo->shared->meals_req))
		return ;
	sem_wait(philo->shared->print);
	printf("%s%lu %d %s\n", clr, get_current_time()
		- philo->shared->start, philo->id, str);
	if (!flag)
		sem_post(philo->shared->print);
}

void	eating(t_philo *philo)
{
	sem_wait(philo->shared->forks);
	printing(philo, WHITE, FORK, 0);
	sem_wait(philo->shared->forks);
	printing(philo, WHITE, FORK, 0);
	sem_wait(philo->shared->lock);
	philo->last_meal = (get_current_time() - philo->shared->start);
	printing(philo, BLUE, EATING, 0);
	sem_post(philo->shared->lock);
	ft_usleep(philo->shared->time_to_eat, philo);
	philo->meals++;
	if (philo->meals == philo->shared->meals_req)
		sem_post(philo->shared->check);
}

void	sleeping(t_philo *philo)
{
	printing(philo, BLACK, SLEEPING, 0);
	sem_post(philo->shared->forks);
	sem_post(philo->shared->forks);
	ft_usleep(philo->shared->time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	printing(philo, YELLOW, THINKING, 0);
}

void	routine(t_philo *philos)
{
	while (1)
	{
		if (philos->id % 2 != 0 && philos->meals == 0)
			ft_usleep(philos->shared->time_to_eat / 2, philos);
		eating(philos);
		sleeping(philos);
		thinking(philos);
	}
}
