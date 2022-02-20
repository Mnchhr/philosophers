/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:24:04 by mkuehl            #+#    #+#             */
/*   Updated: 2022/01/22 13:53:19 by mkuehl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_scan(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->philos_num)
		{
			if (data->philos_num == data->times_all_philos_ate)
				return (1);
			if (data->philos[i].last_meal_time == 0)
				data->philos[i].last_meal_time = data->philos[i].launch_time;
			data->starv_time = ft_get_time() - data->philos[i].last_meal_time;
			if (data->starv_time > (long)data->time_to_die)
			{
				data->dead_philo_id = i + 1;
				return (-1);
			}
			i++;
		}
		usleep(100);
	}
}

int	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philos_num)
		pthread_mutex_destroy(&data->philos[i].fork);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	return (ft_free(data));
}

void	ft_eat_algo(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_print_status(data, philo->id, FORK);
	pthread_mutex_lock(philo->left_fork);
	ft_print_status(data, philo->id, FORK);
	philo->times_ate++;
	ft_print_status(data, philo->id, EAT);
	if (philo->times_ate == data->times_must_eat)
	{
		pthread_mutex_lock(&data->eat_mutex);
		data->times_all_philos_ate++;
		pthread_mutex_unlock(&data->eat_mutex);
	}
	philo->last_meal_time = ft_get_time();
	if (data->philos_num != data->times_all_philos_ate || philo->times_ate == \
		data->times_must_eat)
		ft_eat_philo(data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*ft_run_thread(void *data)
{
	t_data	*tmpdata;
	t_philo	*philo;
	int		i;

	tmpdata = (t_data *)data;
	philo = &tmpdata->philos[tmpdata->turn];
	i = tmpdata->times_must_eat;
	while (i || tmpdata->times_all_philos_ate < tmpdata->philos_num)
	{
		ft_eat_algo(tmpdata, philo);
		if (tmpdata->philos_num == tmpdata->times_all_philos_ate)
			break ;
		ft_sleep_philo(tmpdata, philo->id);
		ft_print_status(tmpdata, philo->id, THINK);
		if (i != -1 && i != 0)
			i--;
	}
	return (NULL);
}

int	ft_start_algo(t_data *data)
{
	data->start_time = ft_get_time();
	data->times_all_philos_ate = 0;
	data->turn = 0;
	if (ft_create_threads(data))
		return (1);
	usleep(500);
	data->turn = 1;
	if (ft_create_threads(data))
		return (1);
	if (ft_scan(data) > 0)
	{
		if (ft_join_threads(data))
			return (1);
	}
	else
	{
		if (ft_detach_threads(data))
			return (1);
	}
	return (0);
}
