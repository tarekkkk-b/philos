/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:10:34 by tabadawi          #+#    #+#             */
/*   Updated: 2024/05/31 22:22:44 by tarekkkk         ###   ########.fr       */
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
	return (TRUE);
}
