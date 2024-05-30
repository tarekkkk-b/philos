/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:14:17 by tarekkkk          #+#    #+#             */
/*   Updated: 2024/05/25 15:15:46 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
