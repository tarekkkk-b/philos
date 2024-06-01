/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:14:55 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/02 00:57:02 by tarekkkk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>

# define INP_ERR	"Usage: ./philo [philos] [time_to_die] [time_to_eat] \
[time_to_sleep] **[meals_required]\n"
# define COUNT		"please use a philospher count in the range of 1 - 200.\n"
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
	int		philo_count;
	int		meals_req;
	size_t	start;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*dead;
}	t_shared;

typedef struct s_philo
{
	int			id;
	int			rf;
	int			lf;
	int			meals;
	pid_t		philo;
	size_t		last_meal;
	t_shared	*shared;
}	t_philo;

int		is_num(int ac, char **av);
int		check_args(int ac, char **av);
int		ft_strlen(char *str);
int		ft_atoi(char *str);
void	ft_usleep(size_t milliseconds, t_philo *philo);
void	routine(t_philo *philos);
void	initializer(t_shared *shared, int ac, char **av);
void	philo_init(t_philo **philo, t_shared *shared);
size_t	get_current_time(void);
void	death(t_shared *shared, t_philo *philo);
int		test(t_philo *philo);

#endif