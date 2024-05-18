/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 16:25:33 by tabadawi          #+#    #+#             */
/*   Updated: 2024/05/17 20:23:53 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef	struct s_philos
{
	pthread_t	philo;
}	t_philos;

typedef	struct	t_shared
{
	int	philos;
	int	ID;
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
		shared->philo[i] = malloc(sizeof(t_philos));
	// {
	// 	shared->philo[i]->ID = i + 1;
	// }
	// while (++i < philo->philos)
	// 	philo->ID[i] = i + 1;
	// philo->philo = malloc(sizeof(pthread_t) * philo->philos);
}

void	eating(t_shared *shared, int id)
{
	pthread_mutex_lock(&shared->eating);
	printf("philo %d: i ate\n", id);
	pthread_mutex_unlock(&shared->eating);
}

void	sleeping(t_shared *shared, int id)
{
	pthread_mutex_lock(&shared->sleeping);
	printf("philo %d: i slept\n", id);
	pthread_mutex_unlock(&shared->sleeping);
}

void	thinking(t_shared *shared, int id)
{
	pthread_mutex_lock(&shared->thinking);
	printf("philo %d: i thought\n", id);
	pthread_mutex_unlock(&shared->thinking);
}

void	*routine(void *shared)
{
	int			i;
	int			j = 3;
	t_shared *tmp;

	tmp = (t_shared *)shared;
	i = tmp->ID;
	pthread_mutex_unlock(&(tmp->ids));
	while (j--)
	{	
		eating(shared, i);
		sleeping(shared, i);
		thinking(shared, i);
	}
	return (NULL);
}

void	create_threads(t_shared	*shared)
{
	int i = -1;
	while (++i < shared->philos)
	{
		pthread_mutex_lock(&shared->ids);
		shared->ID = i + 1;
		pthread_create(&(shared->philo[i]->philo), NULL, routine, (void *)shared);
	}
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
	// int i = 0;
	// while (i < shared.philos)
	// {
	// 	printf("%d\n", shared.philo[i]->ID);
	// 	i++;
	// }
	create_threads(&shared);
	pthread_mutex_destroy(&shared.eating);
	pthread_mutex_destroy(&shared.sleeping);
	pthread_mutex_destroy(&shared.thinking);
	joiner(&shared);
}
