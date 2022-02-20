/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 16:41:47 by mkuehl            #+#    #+#             */
/*   Updated: 2021/12/29 19:06:45 by mkuehl           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' \
		|| c == '\r' || c == ' ')
		return (1);
	return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static	int	ft_calc_num(const char *str, size_t i, int sign)
{
	unsigned long long	num;
	unsigned long long	max;

	num = 0;
	max = 9223372036854775807;
	while (str[i] != '\0' && ft_isdigit(str[i]))
	{
		if (num > (max + 1) && sign == -1)
			return (0);
		if (num > max && sign == 1)
			return (-1);
		num = num * 10 + (str[i++] - '0');
	}
	num = (int)num;
	return (num * sign);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		num;
	int		sign;

	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	num = ft_calc_num(str, i, sign);
	return (num);
}

int	ft_isnumber(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
	}
	return (0);
}
