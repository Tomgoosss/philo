/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:03:01 by tgoossen          #+#    #+#             */
/*   Updated: 2024/12/04 15:32:20 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_program(t_program *program)
{
	int	i;
	int	num_philos;

	i = 0;
	num_philos = program->philos[0].num_of_philos;
	while (i < num_philos)
		pthread_mutex_destroy(&program->forks[i++]);
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->meal_lock);
	pthread_mutex_destroy(&program->write_lock);
}

int	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep2(philo->time_to_sleep, philo);
	return (0);
}

int	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
	return (0);
}
