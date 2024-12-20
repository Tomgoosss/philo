/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:03:16 by tgoossen          #+#    #+#             */
/*   Updated: 2024/12/06 11:41:39 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_ate(t_program *program)
{
	int	i;
	int	finished_eating;

	if (program->philos[0].num_times_to_eat == -1)
		return (0);
	i = 0;
	finished_eating = 0;
	pthread_mutex_lock(&program->meal_lock);
	while (i < program->philos[0].num_of_philos)
	{
		if (program->philos[i].meals_eaten
			>= program->philos[i].num_times_to_eat)
			finished_eating++;
		i++;
	}
	pthread_mutex_unlock(&program->meal_lock);
	if (finished_eating == program->philos[0].num_of_philos)
	{
		pthread_mutex_lock(&program->dead_lock);
		program->dead_flag = 1;
		pthread_mutex_unlock(&program->dead_lock);
		return (1);
	}
	return (0);
}

static int	check_philosopher_death(t_program *program, int i)
{
	size_t	time;

	pthread_mutex_lock(&program->meal_lock);
	time = get_current_time() - program->philos[i].last_meal;
	if (time >= program->philos[i].time_to_die && !program->philos[i].eating)
	{
		print_status(&program->philos[i], "died");
		pthread_mutex_lock(&program->dead_lock);
		program->dead_flag = 1;
		pthread_mutex_unlock(&program->dead_lock);
		pthread_mutex_unlock(&program->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(&program->meal_lock);
	return (0);
}

void	*death_monitor(void *arg)
{
	t_program	*program;
	int			i;

	program = (t_program *)arg;
	while (1)
	{
		i = 0;
		while (i < program->philos[0].num_of_philos)
		{
			if (check_philosopher_death(program, i))
				return (NULL);
			if (check_all_ate(program))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
