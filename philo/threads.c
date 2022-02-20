/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:15:19 by mkuehl            #+#    #+#             */
/*   Updated: 2022/01/21 18:46:10 by mkuehl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_create_threads(t_data *data)
{
	while (data->turn < data->philos_num)
	{
		if (pthread_create(&data->threads[data->turn], NULL, \
			&ft_run_thread, data))
			return (ft_strerror("Error: Couldn't create thread"));
		data->philos[data->turn].launch_time = ft_get_time();
		usleep(100);
		data->turn += 2;
	}
	return (0);
}

int	ft_join_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_num)
	{
		if (pthread_join(data->threads[i], NULL))
			return (ft_strerror("Error: Couldn't join thread"));
	}
	printf("%ld Every philosopher ate %d times\n", ft_get_time() - \
		data->start_time, data->times_must_eat);
	return (0);
}

int	ft_detach_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_detach(data->threads[i]))
			return (ft_strerror("Error: Couldn't detach thread"));
		i++;
	}
	pthread_mutex_lock(&data->print_mutex);
	printf("%ld philosopher %d has died\n", ft_get_time() - data->start_time, \
		data->dead_philo_id);
	return (0);
}

int	ft_free(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->threads)
		free(data->threads);
	if (data)
		free(data);
	return (1);
}
