/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:20:46 by mkuehl            #+#    #+#             */
/*   Updated: 2022/01/21 18:03:09 by mkuehl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	i = 0;
	while (i < data->philos_num)
	{
		array[i].data = data;
		array[i].times_ate = 0;
		array[i].last_meal_time = 0;
		array[i].id = i + 1;
		i++;
	}
	return (array);
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
	data->dead = 0;
	data->philos = ft_init_philos(data);
	if (!data->philos)
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
	if (ft_open_semaphore(data))
		return (ft_free(data));
	if (ft_create_processes(data))
	{
		ft_close_semaphore(data);
		return (ft_free(data));
	}
	ft_free(data);
	return (0);
}
