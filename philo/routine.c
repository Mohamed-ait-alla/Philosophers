/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:58:10 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/22 16:27:58 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	save_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->shared_data->print_mutex);
	printf("%lld %d %s\n", get_time() - philo->shared_data->start_time, philo->philo_id, msg);
	pthread_mutex_unlock(&philo->shared_data->print_mutex);
}

void	philo_think(t_philo *philo)
{
	save_print(philo, "is Thinking\n");
}

void	philo_sleep(t_philo *philo)
{
	save_print(philo, "is sleeping\n");
	usleep(philo->shared_data->time_to_sleep * 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->shared_data->is_dead)
	{
		philo_think(philo);
		// philo_eat();
		philo_sleep(philo);
	}
	return (NULL);
}