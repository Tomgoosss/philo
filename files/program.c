/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:03:18 by tgoossen          #+#    #+#             */
/*   Updated: 2024/12/06 12:15:01 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simulation_end(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(philo->dead_lock);
	is_dead = *philo->dead;
	pthread_mutex_unlock(philo->dead_lock);
	return (is_dead);
}

static void	routine(t_philo *philo)
{
	while (1)
	{
		if (check_simulation_end(philo))
			break ;
		philo_eat(philo);
		if (check_simulation_end(philo))
			break ;
		philo_sleep(philo);
		philo_think(philo);
		ft_usleep(1);
	}
	return ;
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->start_lock);
	pthread_mutex_unlock(philo->start_lock);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
		while (!check_simulation_end(philo))
			usleep(100);
		pthread_mutex_unlock(philo->l_fork);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		ft_usleep2(philo->time_to_eat / 2, philo);
	routine(philo);
	return (NULL);
}

void	set_start_time(t_program *program)
{
	int	i;

	program->philos[0].start_time = get_current_time();
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		program->philos[i].start_time = program->philos[0].start_time;
		i++;
	}
}

int	create_program(t_program *program)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	pthread_mutex_lock(program->philos->start_lock);
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				philosopher_routine, &program->philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, death_monitor, program) != 0)
		return (1);
	set_start_time(program);
	pthread_mutex_unlock(program->philos->start_lock);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
