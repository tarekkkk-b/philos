/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:38:43 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/05/19 14:25:25 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death(t_philos *philo)
{
	if ((get_current_time() - philo->shared->start) - philo->last_meal >= philo->shared->time_to_die)
	{
		printf("\x1b[31m[%lu] philo %d: died\n", 
			(get_current_time() - philo->shared->start), philo->ID);
		return (0);
	}
	return (1);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, t_philos *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&philo->shared->print);
		if (!death(philo))
			exit (1);
		pthread_mutex_unlock(&philo->shared->print);
		usleep(100);
	}
	return (0);
}