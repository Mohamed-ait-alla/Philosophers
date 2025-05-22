/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:44:29 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/22 15:53:19 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
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
	return (current_time.tv_sec * 1000LL);
}
