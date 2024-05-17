/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:25:33 by tabadawi          #+#    #+#             */
/*   Updated: 2024/05/17 17:28:03 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef	struct s_philos
{
	int	ID;
	pthread_t	*philo;
}	t_philos;

typedef	struct	t_shared
{
	int	philos;
	t_philos	**philo;
	pthread_mutex_t eating;
	pthread_mutex_t sleeping;
	pthread_mutex_t thinking;
}	t_shared;

void	check_inp(int ac, char **av, t_shared *shared)
{
	if (ac < 5 || ac > 6)
		exit(1);
	shared->philos = atoi(av[1]);
	int i = -1;
	shared->philo = malloc(sizeof(t_philos) * shared->philos + 1);
	while (++i < shared->philos)
	{
		printf("hi");
		shared->philo[i]->ID = i + 1;
		shared->philo[i]->philo = malloc(sizeof(pthread_t));
	}
	// while (++i < philo->philos)
	// 	philo->ID[i] = i + 1;
	// philo->philo = malloc(sizeof(pthread_t) * philo->philos);
}

// void	eating(t_philos *philo)
// {
// 	pthread_mutex_lock(&philo->eating);
// 	printf("i ate\n");
// 	pthread_mutex_unlock(&philo->eating);
// }

// void	sleeping(t_philos *philo)
// {
// 	pthread_mutex_lock(&philo->sleeping);
// 	printf("i slept\n");
// 	pthread_mutex_unlock(&philo->sleeping);
// }

// void	thinking(t_philos *philo)
// {
// 	pthread_mutex_lock(&philo->thinking);
// 	printf("i thought\n");
// 	pthread_mutex_unlock(&philo->thinking);
// }

// void	*routine(void *philo)
// {
// 	while (1)
// 	{	
// 		eating(philo);
// 		sleeping(philo);
// 		thinking(philo);
// 	}
// 	return (NULL);
// }

// void	create_threads(t_philos *philo)
// {
// 	int i = -1;
// 	while (++i < philo->philos)
// 		pthread_create(&philo->philo[i], NULL, routine, (void *)philo);
// }

// void	joiner(t_philos *philo)
// {
// 	int i = -1;
// 	while (++i < philo->philos)
// 		pthread_join(philo->philo[i], NULL);
// }

int	main(int ac, char **av)
{
	t_shared	shared;

	// pthread_mutex_init(&philo.eating, NULL);
	// pthread_mutex_init(&philo.sleeping, NULL);
	// pthread_mutex_init(&philo.thinking, NULL);
	check_inp(ac, av, &shared);
	int i = 0;
	while (i++ <= shared.philos)
		printf("%d\n", shared.philo[i]->ID);
	// create_threads(&philo);
	// pthread_mutex_destroy(&philo.eating);
	// pthread_mutex_destroy(&philo.sleeping);
	// pthread_mutex_destroy(&philo.thinking);
	// joiner(&philo);
}
