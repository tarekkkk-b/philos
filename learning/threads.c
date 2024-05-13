/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:46:50 by tabadawi          #+#    #+#             */
/*   Updated: 2024/05/11 18:33:01 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void	*routine1()
{
	printf("hi\n");
	return NULL;
}

void	*routine2()
{
	printf("ola\n");
	return NULL;
}

void	*routine3()
{
	printf("hello\n");
	return NULL;
}

int main()
{
	pthread_t philo1;
	pthread_t philo2;
	pthread_t philo3;
	
	pthread_create(&philo1, NULL, routine1, NULL);
	pthread_create(&philo2, NULL, routine2, NULL);
	pthread_create(&philo3, NULL, routine3, NULL);
	pthread_join(philo1, NULL);
	pthread_join(philo2, NULL);
	pthread_join(philo3, NULL);
}