/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:39:08 by tabadawi          #+#    #+#             */
/*   Updated: 2024/05/12 16:22:47 by tabadawi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
	//v1
	struct timeval time;

	gettimeofday(&time, NULL);
	int start  = time.tv_usec;
	printf("time rn %d\n", start);
	usleep(8000000);
	gettimeofday(&time, NULL);
	printf("time rn %llu\n", ((time.tv_sec * (u_int64_t)1000) + (time.tv_usec / 1000)));

	//v2 would have more accuracy, will check on later
}