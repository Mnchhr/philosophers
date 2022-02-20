/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:11:20 by mkuehl            #+#    #+#             */
/*   Updated: 2022/01/21 20:13:12 by mkuehl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (ft_strerror("Error: Wrong number of arguments"));
	i = 0;
	while (argv[++i])
	{
		if (ft_isnumber(argv[i]))
			return (ft_strerror("Error: Invalid argument"));
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || \
		ft_atoi(argv[4]) < 0 || ft_atoi(argv[1]) > 200)
		return (ft_strerror("Error: Invalid argument"));
	if (argc == 6)
	{
		if (ft_atoi(argv[5]) <= 0)
			return (ft_strerror("Error: Invalid argument"));
	}
	return (0);
}

static t_philo	*ft_init_philos(t_data *data)
{
	int		i;
	t_philo	*array;

	array = (t_philo *)malloc(sizeof(t_philo) * data->philos_num);
	if (!array)
	{
		printf("Error: Couldn't allocate memory\n");
		return (NULL);
	}
	i = -1;
	while (++i < data->philos_num)
	{
		array[i].last_meal_time = 0;
		array[i].times_ate = 0;
		array[i].id = i + 1;
		array[i].right_fork = &array[i].fork;
		if (i == (data->philos_num - 1))
			array[i].left_fork = &array[0].fork;
		else
			array[i].left_fork = &array[i + 1].fork;
	}
	return (array);
}

static int	ft_init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philos_num)
	{
		if (pthread_mutex_init(&data->philos[i].fork, NULL))
			return (ft_strerror("Error: Couldn't initialize mutex"));
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (ft_strerror("Error: Couldn't initialize mutex"));
	if (pthread_mutex_init(&data->eat_mutex, NULL))
		return (ft_strerror("Error: Couldn't initialize mutex"));
	return (0);
}

static t_data	*ft_init_data(int argc, char **argv)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
	{
		printf("Error: Couldn't allocate memory\n");
		return (NULL);
	}
	data->philos_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->times_must_eat = ft_atoi(argv[5]);
	else
		data->times_must_eat = -1;
	data->threads = (pthread_t *)malloc(sizeof(pthread_t) * data->philos_num);
	if (!data->threads)
		return (NULL);
	data->philos = ft_init_philos(data);
	if (!data->philos)
		return (NULL);
	if (ft_init_mutexes(data))
		return (NULL);
	return (data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (ft_check_args(argc, argv))
		return (1);
	data = ft_init_data(argc, argv);
	if (!data)
		return (ft_free(data));
	if (ft_start_algo(data))
		return (ft_exit(data));
	ft_exit(data);
	return (0);
}
