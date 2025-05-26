/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:58:10 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/26 14:44:12 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->shared_data->print_mutex);
	if (!philo->shared_data->is_dead)
		printf("%lld %d %s\n", get_time() - philo->shared_data->start_time, philo->philo_id, action);
	pthread_mutex_unlock(&philo->shared_data->print_mutex);
}

void	philo_think(t_philo *philo)
{
	print_action(philo, "is Thinking");
}

void	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo, philo->shared_data->time_to_sleep * 1000);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->shared_data->is_dead)
	{
		// eating
		if (philo->philo_id % 2 == 0)
			usleep(1000);
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		print_action(philo, "is eating");
		pthread_mutex_lock(&philo->shared_data->time_mutex);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->shared_data->time_mutex);
		ft_usleep(philo, philo->shared_data->time_to_eat * 1000);
		philo->n_meals_eaten++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		// sleeping
		philo_sleep(philo);
		// thinking
		philo_think(philo);
	}
	return (NULL);
}
