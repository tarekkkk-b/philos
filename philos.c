/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:25:33 by tabadawi          #+#    #+#             */
/*   Updated: 2024/05/18 15:14:28 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef	struct	s_shared	t_shared;

typedef	struct s_philos
{
	int	ID;
	pthread_t	philo;
	t_shared	*shared;
}	t_philos;

typedef	struct	s_shared
{
	int	philos;
	t_philos	**philo;
	pthread_mutex_t ids;
	pthread_mutex_t eating;
	pthread_mutex_t sleeping;
	pthread_mutex_t thinking;
}	t_shared;

void	check_inp(int ac, char **av, t_shared *shared)
{
	if (ac < 5 || ac > 6)
		exit(1);
	shared->philos = atoi(av[1]);
	shared->philo = malloc(sizeof(t_philos *) * (shared->philos + 1));
	shared->philo[shared->philos] = NULL;
	int i = -1;
	while (++i < shared->philos)
	{
		shared->philo[i] = malloc(sizeof(t_philos));
		shared->philo[i]->ID = i + 1;
		shared->philo[i]->shared = shared;
	}
}

void	eating(t_philos *philo)
{
	pthread_mutex_lock(&philo->shared->eating);
	printf("philo %d: i ate\n", philo->ID); 
	pthread_mutex_unlock(&philo->shared->eating);
}

void	sleeping(t_philos *philo)
{
	pthread_mutex_lock(&philo->shared->sleeping);
	printf("philo %d: i slept\n", philo->ID); 
	pthread_mutex_unlock(&philo->shared->sleeping);
}

void	thinking(t_philos *philo)
{
	pthread_mutex_lock(&philo->shared->thinking);
	printf("philo %d: i thought\n", philo->ID); 
	pthread_mutex_unlock(&philo->shared->thinking);
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

void	create_threads(t_shared	*shared)
{
	int i = -1;
	while (++i < shared->philos)
		pthread_create(&(shared->philo[i]->philo), NULL, routine, (void *)shared->philo[i]);
}

void	joiner(t_shared	*shared)
{
	int i = -1;
	while (++i < shared->philos)
		pthread_join(shared->philo[i]->philo, NULL);
}

int	main(int ac, char **av)
{
	t_shared	shared;

	pthread_mutex_init(&shared.ids, NULL);
	pthread_mutex_init(&shared.eating, NULL);
	pthread_mutex_init(&shared.sleeping, NULL);
	pthread_mutex_init(&shared.thinking, NULL);
	check_inp(ac, av, &shared);
	create_threads(&shared);
	pthread_mutex_destroy(&shared.eating);
	pthread_mutex_destroy(&shared.sleeping);
	pthread_mutex_destroy(&shared.thinking);
	joiner(&shared);
}
