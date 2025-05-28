/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:44:29 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/28 12:30:23 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->shared_data->print_mutex);
	if (check_for_death(philo))
	{
		pthread_mutex_unlock(&philo->shared_data->print_mutex);
		return ;
	}
	printf("%lld %d %s\n", get_time() - philo->shared_data->start_time,
		philo->philo_id, action);
	pthread_mutex_unlock(&philo->shared_data->print_mutex);
}

long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000LL) + (current_time.tv_usec / 1000));
}

int	check_for_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared_data->death_mutex);
	if (philo->shared_data->is_dead)
	{
		pthread_mutex_unlock(&philo->shared_data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->shared_data->death_mutex);
	return (0);
}

void	ft_usleep(t_philo *philo, long long time)
{
	long int	start_time;

	start_time = get_time();
	while (!check_for_death(philo) && (get_time() - start_time) < time)
	{
		if (check_for_death(philo))
			return ;
		usleep(50);
	}
}
