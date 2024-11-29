#include "philo.h"

int	check_simulation_end(t_philo *philo)
{
	int	is_dead;

	pthread_mutex_lock(philo->dead_lock);
	is_dead = *philo->dead;
	pthread_mutex_unlock(philo->dead_lock);
	return (is_dead);
}

void *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    philo->last_meal = get_current_time();
    if (philo->num_of_philos == 1) // one philo
    {
        pthread_mutex_lock(philo->l_fork);
        print_status(philo, "has taken a fork");
        usleep(100);
        pthread_mutex_unlock(philo->l_fork);
        return (NULL);
    }
    if (philo->id % 2 == 0)
        ft_usleep(philo->time_to_eat / 2);
    while (1)
    {
        philo_eat(philo);
        if (check_simulation_end(philo))
             break ;
        philo_sleep(philo);
        if (check_simulation_end(philo))
                break ;
        philo_think(philo);
		if (check_simulation_end(philo))
            break ;
    }
    return (NULL);
}


int create_program(t_program *program)
{
    int i;
    pthread_t monitor;

    i = 0;
    program->philos[0].start_time = get_current_time();
    while (i < program->philos[0].num_of_philos)
    {
        program->philos[i].start_time = program->philos[0].start_time;
        if (pthread_create(&program->philos[i].thread, NULL, 
                          philosopher_routine, &program->philos[i]) != 0)
            return (1);
        i++;
    }
    if (pthread_create(&monitor, NULL, death_monitor, program) != 0)
        return (1);
    pthread_join(monitor, NULL);
    i = 0;
    while (i < program->philos[0].num_of_philos)
    {
        pthread_join(program->philos[i].thread, NULL);
        i++;
    }
    return (0);
}