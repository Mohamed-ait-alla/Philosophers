/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:07:18 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/29 11:35:01 by mait-all         ###   ########.fr       */
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
	if (data->forks)
		free(data->forks);
	if (data->philos)
		free(data->philos);
}

void	start_simulation(t_shared_data *p_data)
{
	pthread_t	monitor_thread;
	int			i;

	i = 0;
	while (i < p_data->nb_philos)
	{
		pthread_create(&p_data->philos[i].thread, NULL,
			&philo_routine, &p_data->philos[i]);
		i++;
	}
	pthread_create(&monitor_thread, NULL, &monitor, p_data);
	i = 0;
	while (i < p_data->nb_philos)
	{
		pthread_join(p_data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}

int	main(int ac, char **av)
{
	t_shared_data	philos_data;

	ac = ac - 1;
	if (ac < 4 || ac > 5 || !av)
	{
		printf("Error: \nUsage: number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat "
			"(optinal)]\n");
		return (1);
	}
	if (init_data(&philos_data, av) == -1)
	{
		write(2, "Invalid Data: args must be positive integers\n", 46);
		return (1);
	}
	start_simulation(&philos_data);
	ft_cleanup(&philos_data);
}
