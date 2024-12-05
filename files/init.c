/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:03:11 by tgoossen          #+#    #+#             */
/*   Updated: 2024/12/05 13:59:05 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo_values(t_philo *philo, char **argv, int argc, int i)
{
	philo->id = i + 1;
	philo->eating = 0;
	philo->meals_eaten = 0;
	philo->last_meal = get_current_time();
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->num_times_to_eat = -1;
	if (argc == 6)
		philo->num_times_to_eat = ft_atoi(argv[5]);
}

static void	init_philos(t_program *program, char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&program->forks[i], NULL);
		init_philo_values(&program->philos[i], argv, argc, i);
		program->philos[i].dead = &program->dead_flag;
		program->philos[i].l_fork = &program->forks[i];
		program->philos[i].r_fork = &program->forks[(i + 1) % ft_atoi(argv[1])];
		program->philos[i].write_lock = &program->write_lock;
		program->philos[i].dead_lock = &program->dead_lock;
		program->philos[i].meal_lock = &program->meal_lock;
		program->philos[i].start_lock = &program->start_lock;
		i++;
	}
}

int	init_all(int argc, char **argv, t_program *program)
{
	program->dead_flag = 0;
	if (pthread_mutex_init(&program->dead_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&program->meal_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&program->write_lock, NULL) != 0)
		return (1);
	init_philos(program, argv, argc);
	return (0);
}
