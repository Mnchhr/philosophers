/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:20:04 by mkuehl            #+#    #+#             */
/*   Updated: 2022/01/21 18:53:02 by mkuehl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*ft_scan(void *philo)
{
	t_philo	*philosopher;
	t_data	*data;

	philosopher = (t_philo *)philo;
	data = philosopher->data;
	while (1)
	{
		sem_wait(data->scan_sem);
		data->starv_time = ft_get_time() - philosopher->last_meal_time;
		if (data->starv_time > (long)data->time_to_die)
		{
			sem_wait(data->print_sem);
			data->dead = 1;
			printf("%ld philosopher %d died\n", ft_get_time() - \
				data->start_time, philosopher->id);
			exit (1);
		}
		sem_post(data->scan_sem);
		if (data->dead || (philosopher->times_ate >= data->times_must_eat && \
			data->times_must_eat != -1))
			break ;
		usleep(1000);
	}
	return (NULL);
}

static void	ft_eat_algo(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->forks);
	ft_print_status(data, philo->id, FORK);
	sem_wait(data->forks);
	ft_print_status(data, philo->id, FORK);
	philo->last_meal_time = ft_get_time();
	ft_eat_philo(data, philo->id);
	philo->times_ate++;
	sem_post(data->forks);
	sem_post(data->forks);
}

static void	ft_run_algo(t_data *data, t_philo *philo)
{
	philo->last_meal_time = ft_get_time();
	pthread_create(&(data->scan), NULL, ft_scan, (void *)philo);
	if (philo->pid % 2)
		usleep(500);
	while (!data->dead)
	{
		ft_eat_algo(philo);
		if (philo->times_ate == data->times_must_eat)
			break ;
		ft_sleep_philo(data, philo->id);
		ft_print_status(data, philo->id, THINK);
	}
	pthread_detach(data->scan);
	if (data->dead)
		exit (1);
	exit (0);
}

static void	ft_destroy_processes(t_data *data)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < data->philos_num)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < data->philos_num)
				kill(data->philos[i].pid, SIGTERM);
			break ;
		}
	}
	if (!data->dead && data->times_must_eat != -1)
		printf("%ld Every philosopher ate %d times\n", ft_get_time() - \
			data->start_time, data->times_must_eat);
	ft_close_semaphore(data);
}

int	ft_create_processes(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = ft_get_time();
	while (++i < data->philos_num)
	{
		data->philos[i].pid = fork();
		data->philos[i].launch_time = ft_get_time();
		if (data->philos[i].pid < 0)
			return (ft_strerror("Error: Couldn't create processes"));
		else if (data->philos[i].pid == 0)
			ft_run_algo(data, &data->philos[i]);
		usleep(100);
	}
	ft_destroy_processes(data);
	return (0);
}
