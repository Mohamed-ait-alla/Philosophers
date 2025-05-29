/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 11:50:50 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/29 11:54:07 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_n_of_times_eaten(t_shared_data *data)
{
	int	counter;
	int	i;
	int	meals_eaten;

	counter = 0;
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->meals_eaten_mutex);
		meals_eaten = data->philos[i].n_meals_eaten;
		pthread_mutex_unlock(&data->meals_eaten_mutex);
		if (meals_eaten == data->nb_of_times_each_philosopher_must_eat)
			counter++;
		i++;
	}
	return (counter);
}

static int	has_been_death(t_shared_data *data)
{
	long long		current_time;
	long long		last_meal_time;
	int				i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->time_mutex);
		current_time = get_time();
		last_meal_time = data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->time_mutex);
		if (current_time - last_meal_time >= data->time_to_die)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->death_mutex);
			if (data->nb_philos != 1)
				printf("%lld %d is dead\n", get_time()
					- data->start_time, data->philos[i].philo_id);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void	*arg)
{
	t_shared_data	*data;

	data = (t_shared_data *)arg;
	while (1)
	{
		if (check_for_death(&data->philos[0]))
			break ;
		if (has_been_death(data))
			return (NULL);
		if (data->nb_of_times_each_philosopher_must_eat > 0)
		{
			if (check_n_of_times_eaten(data) >= data->nb_philos)
			{
				pthread_mutex_lock(&data->death_mutex);
				printf("all philos had eaten "
					"[nb_of_times_each_philosopher_must_eat]\n");
				data->is_dead = 1;
				pthread_mutex_unlock(&data->death_mutex);
				return (NULL);
			}
		}
		usleep(1000);
	}
	return (NULL);
}
