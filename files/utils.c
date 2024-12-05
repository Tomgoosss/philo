/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:03:21 by tgoossen          #+#    #+#             */
/*   Updated: 2024/12/05 13:46:14 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <philo.h>

long	ft_atoi(const char *nptr)
{
	int		i;
	int		r;
	long	result;

	i = 0;
	r = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		r = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		if (result > INT_MAX && r == 1)
			return (INT_MAX + 1L);
		if (result > ((long)INT_MAX + 1) && r == -1)
			return (INT_MIN - 1L);
		i++;
	}
	return (r * result);
}

long int	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(philo->write_lock);
	if (!check_simulation_end(philo))
		printf("%zu %d %s\n", get_current_time() - philo->start_time, philo->id,
			status);
	pthread_mutex_unlock(philo->write_lock);
}

int	ft_usleep(long int time)
{
	long int	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < time)
		usleep(150);
	return (1);
}

int	ft_usleep2(long int time, t_philo *philo)
{
	long int	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time)
		< time && !check_simulation_end(philo))
		usleep(150);
	return (1);
}
