#include "philo.h"

void	update_last_meal_time(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->meal_lock);
}

void	increment_meals_eaten(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		print_status(philo, "has taken a fork");
	}
}

void	philo_eat(t_philo *philo)
{
	pick_up_forks(philo);
	update_last_meal_time(philo);
	print_status(philo, "is eating");
	ft_usleep2(philo->time_to_eat, philo);
	increment_meals_eaten(philo);
	put_down_forks(philo);
}

int philo_sleep(t_philo *philo)
{
    print_status(philo, "is sleeping");
    ft_usleep2(philo->time_to_sleep, philo);
    // ft_usleep(philo->time_to_sleep);
    return (0);
}

int philo_think(t_philo *philo)
{
    print_status(philo, "is thinking");
    return (0);
} 