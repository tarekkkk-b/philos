/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:02:32 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/05/20 19:36:02 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philos	*philo)
{
	pthread_mutex_lock(&philo->rfork);
	if (!philo->rf)
		if (philo->avail)
		{
			philo->rf = 1;
			philo->avail = 0;
			// printf("\x1b[37m[%lu] philo %d: picked up the right fork\n", 
			// 	(get_current_time() - philo->shared->start), philo->ID);
		}
	pthread_mutex_unlock(&philo->rfork);
	pthread_mutex_lock(&philo->lfork);
	if (!philo->lf)
	{
		if (philo->ID == 1)
		{
			if (philo->shared->philo[philo->shared->philos - 1]->avail)
			{
				philo->lf = 1;
				philo->shared->philo[philo->shared->philos - 1]->avail = 0;
				// printf("\x1b[37m[%lu] philo %d: picked up the left fork\n", 
				// 	(get_current_time() - philo->shared->start), philo->ID);
			}
		}
		else
			if (philo->shared->philo[philo->ID - 2]->avail)
			{
				philo->lf = 1;
				philo->shared->philo[philo->ID - 2]->avail = 0;
				// printf("\x1b[37m[%lu] philo %d: picked up the left fork\n", 
				// 	(get_current_time() - philo->shared->start), philo->ID);
			}
	}
	pthread_mutex_unlock(&philo->lfork);
	if (philo->rf && philo->lf)
		return (1);
	return (0);

}

void	drop_forks(t_philos	*philo)
{
	if (philo->state == 1)
	{
		pthread_mutex_lock(&philo->rfork);
		philo->rf = 0;
		// printf("\x1b[37m[%lu] philo %d: dropped the right fork\n", 
		// 	(get_current_time() - philo->shared->start), philo->ID);
		pthread_mutex_unlock(&philo->rfork);
		pthread_mutex_lock(&philo->lfork);
		philo->lf = 0;
		// printf("\x1b[37m[%lu] philo %d: dropped the left fork\n", 
		// 	(get_current_time() - philo->shared->start), philo->ID);
		pthread_mutex_unlock(&philo->lfork);
		philo->avail = 1;
		pthread_mutex_lock(&philo->available);
		if (philo->ID == 1)
			philo->shared->philo[philo->shared->philos - 1]->avail = 1;
		else
			philo->shared->philo[philo->ID - 2]->avail = 1;
		pthread_mutex_unlock(&philo->available);
		return	;	
	}
	return	;
}