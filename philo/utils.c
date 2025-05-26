/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:44:29 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/26 16:17:56 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	is_valid_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i = 1;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (!is_valid_number(str))
		return (-1);
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		if (result >= 2147483648)
			return (-1);
		result = (result * 10) + (*str - 48);
		str++;
	}
	return (sign * (int)result);
}

long long	get_time(void)
{
	struct timeval current_time;
	
	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000LL + current_time.tv_usec / 1000);
}

void	ft_usleep(t_philo *philo, long time)
{
	long	devided_time;

	devided_time = 0;
	while (time >= devided_time && !philo->shared_data->is_dead)
	{
		usleep(1000);
		devided_time += 1000;
	}
}
