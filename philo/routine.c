/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:58:10 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/28 17:12:07 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	print_action(philo, "is sleeping");
	ft_usleep(philo, philo->shared_data->time_to_sleep);
}

void	take_the_forks(t_philo *philo)
{
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
}

void	put_the_forks(t_philo *philo)
{
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

void	philo_eat(t_philo *philo)
{
	if (philo->shared_data->nb_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		ft_usleep(philo, philo->shared_data->time_to_die);
		pthread_mutex_lock(&philo->shared_data->death_mutex);
		philo->shared_data->is_dead = 1;
		pthread_mutex_unlock(&philo->shared_data->death_mutex);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		take_the_forks(philo);
		pthread_mutex_lock(&philo->shared_data->time_mutex);
		philo->last_meal_time = get_time();
		pthread_mutex_unlock(&philo->shared_data->time_mutex);
		pthread_mutex_lock(&philo->shared_data->meals_eaten_mutex);
		philo->n_meals_eaten++;
		pthread_mutex_unlock(&philo->shared_data->meals_eaten_mutex);
		print_action(philo, "is eating");
		ft_usleep(philo, philo->shared_data->time_to_eat);
		put_the_forks(philo);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_for_death(philo))
			break ;
		print_action(philo, "is Thinking");
		if (check_for_death(philo))
			break ;
		philo_eat(philo);
		if (check_for_death(philo))
			break ;
		philo_sleep(philo);
	}
	return (NULL);
}
