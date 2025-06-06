/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-all <mait-all@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:07:15 by mait-all          #+#    #+#             */
/*   Updated: 2025/05/28 11:54:52 by mait-all         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_shared_data	t_shared_data;
typedef struct s_philo
{
	int							philo_id;
	int							n_meals_eaten;
	long long					last_meal_time;
	pthread_t					thread;
	pthread_mutex_t				*left_fork;
	pthread_mutex_t				*right_fork;
	t_shared_data				*shared_data;
}								t_philo;

typedef struct s_shared_data
{
	int							nb_philos;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							nb_of_times_each_philosopher_must_eat;
	int							is_dead;
	long long					start_time;
	pthread_mutex_t				print_mutex;
	pthread_mutex_t				time_mutex;
	pthread_mutex_t				death_mutex;
	pthread_mutex_t				monitor_mutex;
	pthread_mutex_t				meals_eaten_mutex;
	pthread_mutex_t				*forks;
	t_philo						*philos;
}								t_shared_data;
long long	get_time(void);
int			ft_atoi(const char *s);
int			init_data(t_shared_data *philos_data, char **av);
int			check_for_death(t_philo *philo);
void		*philo_routine(void *arg);
void		ft_usleep(t_philo *philo, long long time);
void		print_action(t_philo *philo, char *action);
void		*monitor(void	*arg);
#endif