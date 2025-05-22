/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:07:18 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/22 15:55:13 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	ac = ac - 1;
	if (ac < 4 || ac > 5 || !av)
	{
		printf("Error: \nUsage: number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat (optinal)]\n");
		exit(EXIT_FAILURE);
	}
	t_shared_data philos_data;
	init_data(&philos_data, av);
}