/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 18:33:10 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/05/20 19:31:19 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef	struct	s_shared	t_shared;

typedef	struct s_philos
{
	int				ID;
	int				meals;
	int				avail;
	int				rf;
	int				lf;
	int				state;
	pthread_t		philo;
	t_shared		*shared;
	size_t			last_meal;
	pthread_mutex_t	lfork;
	pthread_mutex_t	rfork;
	pthread_mutex_t	m_state;
	pthread_mutex_t	available;
}	t_philos;

typedef	struct	s_shared
{
	int				philos;
	t_philos		**philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start;
	int				meals;
	int				died;
	pthread_mutex_t	print;
}	t_shared;

int		ft_usleep(size_t milliseconds, t_philos *philo);
void	*routine(void *philo);
void	eating(t_philos *philo);
void	sleeping(t_philos *philo);
void	thinking(t_philos *philo);
void	create_threads(t_shared	*shared);
void	joiner(t_shared	*shared);
void	check_inp(int ac, char **av, t_shared *shared);
size_t	get_current_time(void);
int		death(t_philos *philo);
int		take_forks(t_philos	*philo);
void	drop_forks(t_philos	*philo);

#endif