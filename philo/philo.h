/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:57:20 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/06/08 15:27:01 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# define INP_ERR	"Usage: ./philo [philos] [time_to_die] [time_to_eat] \
[time_to_sleep] **[meals_required]\n"
# define COUNT		"please use a philospher count in the range of 1 - 200.\n"
# define NUMBER		"please use a number in the range of 1 - 2147483647.\n"
# define DEATH		"died"
# define EATING		"is eating"
# define SLEEPING	"is sleeping"
# define THINKING	"is thinking"
# define FORK		"has taken a fork"
# define TRUE		1
# define FALSE		0
# define BLACK		"\x1b[30m"
# define RED		"\x1b[31m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define WHITE		"\x1b[37m"

typedef struct s_shared
{
	int				philo_count;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				meals_req;
	int				died;
	int				*forks;
	size_t			start;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	last_meal_m;
	pthread_mutex_t	meal_m;
	pthread_mutex_t	check;
	pthread_mutex_t	extra;
	pthread_mutex_t	*forks_m;
}	t_shared;

typedef struct s_philo
{
	int				id;
	int				rf;
	int				lf;
	int				meals;
	size_t			last_meal;
	t_shared		*shared;
	pthread_t		philo;
}	t_philo;

int		check_args(int ac, char **av);
int		ft_strlen(char *str);
int		ft_atoi(char *str);
int		initializer(t_shared *shared, int ac, char **av);
int		philo_init(t_philo **philo, t_shared *shared);
size_t	get_current_time(void);
void	*routine(void *p);
int		take_forks(t_philo *philo);
void	drop_forks(t_philo *philo);
int		ft_usleep(size_t milliseconds, t_philo *philo);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);
int		thinking(t_philo *philo);
int		death(t_philo *philo);
void	freeer(t_philo **philo, t_shared *shared);
void	create_threads(t_philo **philo);
void	joiner(t_philo	**philo);
void	freeer(t_philo **philo, t_shared *shared);
void	destroyer(t_shared *shared);
int		checker(int value, pthread_mutex_t lock);
void	print(t_philo *philo, pthread_mutex_t *lock, char *str, char *colour);
void	err_free(t_shared *shared, t_philo **philo, int ind);

#endif