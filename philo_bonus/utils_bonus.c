/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:18:38 by mkuehl            #+#    #+#             */
/*   Updated: 2022/01/21 16:07:08 by mkuehl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	ft_sleep_philo(t_data *data, int id)
{
	long	sleep_time;

	ft_print_status(data, id, SLEEP);
	sleep_time = ft_get_time() + (long)data->time_to_sleep;
	while (ft_get_time() < sleep_time && !data->dead)
		usleep(100);
}

void	ft_eat_philo(t_data *data, int id)
{
	long	eat_time;

	ft_print_status(data, id, EAT);
	eat_time = ft_get_time() + (long)data->time_to_eat;
	while (ft_get_time() < eat_time && !data->dead)
		usleep(100);
}

void	ft_print_status(t_data *data, int id, char *str)
{
	sem_wait(data->print_sem);
	if (!data->dead)
	{
		printf("%ld philosopher %d %s\n", ft_get_time() - data->start_time, \
			id, str);
	}
	sem_post(data->print_sem);
}
