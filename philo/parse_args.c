/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:40:09 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/27 22:12:05 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_shared_data *data, char **av)
{
	if (data->nb_philos <= 0
		|| data->time_to_die <= 0
		|| data->time_to_eat <= 0
		|| data->time_to_sleep <= 0
		|| data->nb_of_times_each_philosopher_must_eat < 0
		|| (data->nb_of_times_each_philosopher_must_eat == 0 && av[5]))
		return (0);
	return (1);
}

int	init_data(t_shared_data *philos_data, char **av)
{
	int	i;
	
	philos_data->nb_philos = ft_atoi(av[1]);
	philos_data->time_to_die = ft_atoi(av[2]);
	philos_data->time_to_eat = ft_atoi(av[3]);
	philos_data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
			philos_data->nb_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		philos_data->nb_of_times_each_philosopher_must_eat = 0;
	if (!check_args(philos_data, av))
		return (-1);
	philos_data->is_dead = 0;
	philos_data->start_time = get_time();
	pthread_mutex_init(&philos_data->print_mutex, NULL);
	pthread_mutex_init(&philos_data->time_mutex, NULL);
	pthread_mutex_init(&philos_data->monitor_mutex, NULL);
	pthread_mutex_init(&philos_data->meals_eaten_mutex, NULL);
	pthread_mutex_init(&philos_data->death_mutex, NULL);
	pthread_mutex_init(&philos_data->monitor_counter_mutex, NULL);
	philos_data->forks = malloc(sizeof(pthread_mutex_t) * philos_data->nb_philos);
	if (!philos_data->forks)
		return (-1);
	i = 0;
	while (i < philos_data->nb_philos)
	{
		pthread_mutex_init(&philos_data->forks[i], NULL);
		i++;
	}
	philos_data->philos = malloc(sizeof(t_philo) * philos_data->nb_philos);
	if (!philos_data->philos)
		return (-1);
	i = 0;
	while (i < philos_data->nb_philos)
	{
		philos_data->philos[i].philo_id = i + 1;
		philos_data->philos[i].n_meals_eaten = 0; // didn't eat anything
		philos_data->philos[i].last_meal_time = philos_data->start_time;
		philos_data->philos[i].left_fork = &philos_data->forks[i];
		philos_data->philos[i].right_fork = &philos_data->forks[(i + 1) % philos_data->nb_philos];
		philos_data->philos[i].shared_data = philos_data;
		i++;
	}
	return (0);
}
