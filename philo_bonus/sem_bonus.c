/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:19:11 by mkuehl            #+#    #+#             */
/*   Updated: 2022/01/21 17:12:25 by mkuehl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_open_semaphore(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("scan");
	data->forks = sem_open("forks", O_CREAT, S_IRWXU, data->philos_num);
	data->print_sem = sem_open("print", O_CREAT, S_IRWXU, 1);
	data->scan_sem = sem_open("scan", O_CREAT, S_IRWXU, 1);
	if (data->forks <= 0 || data->print_sem <= 0 || data->scan_sem <= 0)
		return (ft_strerror("Error: Couldn't initialize semaphores"));
	return (0);
}

int	ft_close_semaphore(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print_sem);
	sem_close(data->scan_sem);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("scan");
	return (0);
}

int	ft_free(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data)
		free(data);
	return (1);
}

int	ft_strerror(char *str)
{
	printf("%s\n", str);
	return (1);
}
