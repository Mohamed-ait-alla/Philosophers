/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:58:10 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/27 22:34:14 by mait-all         ###   ########.fr       */
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
	ft_usleep(philo, philo->shared_data->time_to_sleep);
}

void	philo_eat(t_philo *philo)
{
	// if (philo->philo_id % 2 == 0)
	// 	usleep(1000);
	// 	pthread_mutex_lock(philo->right_fork);
	// else
	// 	pthread_mutex_lock(philo->left_fork);
	// print_action(philo, "has taken a fork");
	// if (philo->philo_id % 2)
	// 	pthread_mutex_lock(philo->left_fork);
	// else
	// 	pthread_mutex_lock(philo->right_fork);
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		usleep(1000);
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");	
	}
	pthread_mutex_lock(&philo->shared_data->time_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->shared_data->time_mutex);
	pthread_mutex_lock(&philo->shared_data->meals_eaten_mutex);
	philo->n_meals_eaten++;
	pthread_mutex_unlock(&philo->shared_data->meals_eaten_mutex);
	print_action(philo, "is eating");
	ft_usleep(philo, philo->shared_data->time_to_eat);
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_for_death(philo))
			break;
		philo_think(philo);
		if (check_for_death(philo))
			break;
		philo_eat(philo);
		if (check_for_death(philo))
			break;
		philo_sleep(philo);
	}
	return (NULL);
}
