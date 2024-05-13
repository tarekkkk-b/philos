/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:25:33 by tabadawi          #+#    #+#             */
/*   Updated: 2024/05/13 15:44:45 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef	struct s_philos
{
	int	philos;
	int	*ID;
	pthread_mutex_t eating;
	pthread_mutex_t sleeping;
	pthread_mutex_t thinking;
	pthread_t	*philo;
}	t_philos;

void	check_inp(int ac, char **av, t_philos *philo)
{
	if (ac < 5 || ac > 6)
		exit(1);
	philo->philos = atoi(av[1]);
	int i = -1;
	philo->ID = malloc(sizeof(int) * philo->philos);
	while (++i < philo->philos)
		philo->ID[i] = i + 1;
	philo->philo = malloc(sizeof(pthread_t) * philo->philos);
}

void	eating(t_philos *philo)
{
	printf("i ate\n");
}

void	sleeping(t_philos *philo)
{
	printf("i slept\n");
}

void	thinking(t_philos *philo)
{
	printf("i thought\n");
}

void	*routine(void *philo)
{
	while (1)
	{	
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	create_threads(t_philos *philo)
{
	int i = -1;
	while (++i < philo->philos)
		pthread_create(&philo->philo[i], NULL, routine, (void *)philo);
}

void	joiner(t_philos *philo)
{
	int i = -1;
	while (++i < philo->philos)
		pthread_join(philo->philo[i], NULL);
}

int	main(int ac, char **av)
{
	t_philos philo;

	check_inp(ac, av, &philo);
	create_threads(&philo);
	joiner(&philo);
}