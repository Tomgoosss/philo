#include "philo.h"

int philo_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->l_fork);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(philo->r_fork);
    print_status(philo, "has taken a fork");
    
    pthread_mutex_lock(philo->meal_lock);
    philo->eating = 1;
    philo->last_meal = get_current_time();
    print_status(philo, "is eating");
    
    if (philo->num_times_to_eat == -1 || 
        philo->meals_eaten < philo->num_times_to_eat)
        philo->meals_eaten++;
        
    pthread_mutex_unlock(philo->meal_lock);
    
    ft_usleep(philo->time_to_eat);
    philo->eating = 0;
    
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
    
    return (*philo->dead);
}

int philo_sleep(t_philo *philo)
{
    print_status(philo, "is sleeping");
    ft_usleep(philo->time_to_sleep);
    return (*philo->dead);
}

int philo_think(t_philo *philo)
{
    print_status(philo, "is thinking");
    return (*philo->dead);
} 