/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 14:19:33 by mkuehl            #+#    #+#             */
/*   Updated: 2022/01/21 17:12:32 by mkuehl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <pthread.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_philo
{
	int				id;
	int				times_ate;
	pid_t			pid;
	long			last_meal_time;
	long			launch_time;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				dead;
	int				philos_num;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				times_must_eat;
	long			starv_time;
	long			start_time;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*scan_sem;
	pthread_t		scan;
}	t_data;

int		ft_atoi(const char *str);
int		ft_isnumber(char *str);
void	ft_sleep_philo(t_data *data, int id);
void	ft_eat_philo(t_data *data, int id);
long	ft_get_time(void);
void	ft_print_status(t_data *data, int id, char *str);
int		ft_open_semaphore(t_data *data);
int		ft_close_semaphore(t_data *data);
int		ft_create_processes(t_data *data);
int		ft_free(t_data *data);
int		ft_strerror(char *str);

#endif