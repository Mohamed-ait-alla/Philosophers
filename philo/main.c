/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:07:18 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/26 15:08:34 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_n_of_times_eaten(t_shared_data *data)
{
	int	counter;
	int	i;
	
	counter = 0;
	i = 0;
	while (i < data->nb_philos && !data->is_dead)
	{		
		if (data->philos[i].n_meals_eaten >= data->nb_of_times_each_philosopher_must_eat)
			counter++;
		i++;
	}
	return (counter);
}

void	*monitor_check(void	*arg)
{
	t_shared_data	*data;
	int				i;

	data = (t_shared_data *)arg;
	while (!data->is_dead)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_lock(&data->monitor_mutex);
			if (get_time() - data->philos[i].last_meal_time >= data->time_to_die)
			{
				print_action(&data->philos[i], "is dead");
				data->is_dead = 1;
				pthread_mutex_unlock(&data->monitor_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&data->monitor_mutex);
			i++;	
		}
		// data race may be here
		if (data->nb_of_times_each_philosopher_must_eat > 0 && (check_n_of_times_eaten(data) == data->nb_philos))
		{
			data->is_dead = 1;
			return (NULL);
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	ac = ac - 1;
	pthread_t	monitor;
	if (ac < 4 || ac > 5 || !av)
	{
		printf("Error: \nUsage: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat (optinal)]\n");
		exit(EXIT_FAILURE);
	}
	t_shared_data philos_data;
	init_data(&philos_data, av);
	int	i = 0;
	while (i < philos_data.nb_philos)
	{
		pthread_create(&philos_data.philos[i].thread, NULL, &philo_routine, &philos_data.philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, &monitor_check, &philos_data);
	i = 0;
	while (i < philos_data.nb_philos)
	{
		pthread_join(philos_data.philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}
