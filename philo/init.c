/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 09:40:09 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/28 12:27:33 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(t_shared_data *data, char **av)
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

static int	init_philo(t_shared_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (-1);
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].philo_id = i + 1;
		data->philos[i].n_meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		data->philos[i].shared_data = data;
		i++;
	}
	return (0);
}

static int	init_mutexes(t_shared_data *data)
{
	int	i;

	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->time_mutex, NULL);
	pthread_mutex_init(&data->monitor_mutex, NULL);
	pthread_mutex_init(&data->meals_eaten_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (-1);
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_data(t_shared_data *philos_data, char **av)
{
	philos_data->nb_philos = ft_atoi(av[1]);
	philos_data->time_to_die = ft_atoi(av[2]);
	philos_data->time_to_eat = ft_atoi(av[3]);
	philos_data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philos_data->nb_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		philos_data->nb_of_times_each_philosopher_must_eat = 0;
	philos_data->is_dead = 0;
	philos_data->start_time = get_time();
	if (!check_args(philos_data, av))
		return (-1);
	if (init_mutexes(philos_data) < 0)
		return (-1);
	if (init_philo(philos_data) < 0)
		return (-1);
	return (0);
}
