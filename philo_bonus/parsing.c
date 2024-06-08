/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:10:34 by tabadawi          #+#    #+#             */
/*   Updated: 2024/06/08 15:26:02 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_num(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		if (av[i][0] == '+' || av[i][0] == '-')
			j++;
		while (av[i][++j])
			if (!(av[i][j] >= '0' && av[i][j] <= '9'))
				return (FALSE);
	}
	return (TRUE);
}

int	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6 || !(is_num(ac, av)))
		return ((void)write(1, INP_ERR, ft_strlen(INP_ERR)), FALSE);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 200)
		return ((void)write(1, COUNT, ft_strlen(COUNT)), FALSE);
	if (ft_atoi(av[2]) < 1 || ft_atoi(av[2]) > INT_MAX)
		return ((void)write(1, NUMBER, ft_strlen(NUMBER)), FALSE);
	if (ft_atoi(av[3]) < 1 || ft_atoi(av[3]) > INT_MAX)
		return ((void)write(1, NUMBER, ft_strlen(NUMBER)), FALSE);
	if (ft_atoi(av[4]) < 1 || ft_atoi(av[4]) > INT_MAX)
		return ((void)write(1, NUMBER, ft_strlen(NUMBER)), FALSE);
	if (ac == 6)
		if (ft_atoi(av[5]) < 1 || ft_atoi(av[5]) > INT_MAX)
			return ((void)write(1, NUMBER, ft_strlen(NUMBER)), FALSE);
	return (TRUE);
}
