/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 14:55:14 by mkuehl            #+#    #+#             */
/*   Updated: 2022/01/21 20:53:41 by mkuehl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	while (ft_get_time() < sleep_time)
		usleep(100);
}

void	ft_eat_philo(t_data *data)
{
	long	eat_time;

	eat_time = ft_get_time() + (long)data->time_to_eat;
	while (ft_get_time() < eat_time)
		usleep(100);
}

void	ft_print_status(t_data *data, int id, char *str)
{
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld philosopher %d %s\n", ft_get_time() - data->start_time, id, str);
	pthread_mutex_unlock(&data->print_mutex);
}

int	ft_strerror(char *str)
{
	printf("%s\n", str);
	return (1);
}
