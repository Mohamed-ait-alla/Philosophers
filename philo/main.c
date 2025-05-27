/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:07:18 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/27 22:13:02 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_cleanup(t_shared_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->monitor_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->time_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_destroy(&data->monitor_counter_mutex);
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

static int	check_n_of_times_eaten(t_shared_data *data)
{
	int	counter;
	int	i;
	int meals_eaten;
	
	counter = 0;
	i = 0;
	while (i < data->nb_philos)
	{	
		pthread_mutex_lock(&data->meals_eaten_mutex);
		meals_eaten = data->philos[i].n_meals_eaten;
		pthread_mutex_unlock(&data->meals_eaten_mutex);
		if (meals_eaten == data->nb_of_times_each_philosopher_must_eat)
		{
			pthread_mutex_lock(&data->monitor_counter_mutex);	
			counter++;
			pthread_mutex_unlock(&data->monitor_counter_mutex);	
		}
		i++;
	}
	return (counter);
}

void	*monitor_check(void	*arg)
{
	t_shared_data	*data;
	int				i;
	long long		current_time;
	long long		last_meal_time;

	data = (t_shared_data *)arg;
	while (1)
	{
		if (check_for_death(&data->philos[0]))
			break;
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
				printf("%lld %d is dead\n", get_time()
						- data->start_time, data->philos[i].philo_id);
				return (NULL);
			}
			i++;	
		}
		if (data->nb_of_times_each_philosopher_must_eat > 0)
		{
			if (check_n_of_times_eaten(data) >= data->nb_philos)
			{
				pthread_mutex_lock(&data->monitor_mutex);
				printf("rahom salow\n");
				data->is_dead = 1;
				pthread_mutex_unlock(&data->monitor_mutex);
				return (NULL);
			}
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
	if (init_data(&philos_data, av) == -1)
	{
		write(2, "Invalid Data: args must be positive integers\n", 46);
		return (EXIT_FAILURE);
	}
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
	ft_cleanup(&philos_data);
}
