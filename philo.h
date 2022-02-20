/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:12:07 by mkuehl            #+#    #+#             */
/*   Updated: 2022/01/21 20:53:58 by mkuehl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_philo
{
	int				id;
	long			last_meal_time;
	long			launch_time;
	int				times_ate;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	fork;
}	t_philo;

typedef struct s_data
{
	int				turn;
	int				philos_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				times_must_eat;
	int				times_all_philos_ate;
	long			starv_time;
	long			start_time;
	int				dead_philo_id;
	t_philo			*philos;
	pthread_t		*threads;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	eat_mutex;
}	t_data;

int		ft_atoi(const char *str);
int		ft_isnumber(char *str);
int		ft_free(t_data *data);
void	ft_sleep_philo(t_data *data, int id);
void	ft_eat_philo(t_data *data);
int		ft_start_algo(t_data *data);
long	ft_get_time(void);
void	ft_print_status(t_data *data, int id, char *str);
void	*ft_run_thread(void *data);
int		ft_create_threads(t_data *data);
int		ft_join_threads(t_data *data);
int		ft_detach_threads(t_data *data);
int		ft_exit(t_data *data);
int		ft_strerror(char *str);

#endif