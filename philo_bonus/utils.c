/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:15:31 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/08 15:21:48 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	(void)philo;
	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(100);
}

void	close_semaphores(t_shared *shared)
{
	sem_close(shared->forks);
	sem_close(shared->print);
	sem_close(shared->dead);
	sem_close(shared->pause);
	sem_close(shared->lock);
	if (shared->meals_req != -1)
		sem_close(shared->check);
	sem_unlink("/sem_forks");
	sem_unlink("/sem_pause");
	sem_unlink("/sem_print");
	sem_unlink("/sem_dead");
	sem_unlink("/sem_check");
	sem_unlink("/sem_lock");
}
