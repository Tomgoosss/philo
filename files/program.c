#include "philo.h"

void *philosopher_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    philo->last_meal = get_current_time();
    
    // If only one philosopher, handle special case
    if (philo->num_of_philos == 1)
    {
        pthread_mutex_lock(philo->l_fork);
        print_status(philo, "has taken a fork");
        while (!*philo->dead)
            usleep(100);
        pthread_mutex_unlock(philo->l_fork);
        return (NULL);
    }

    // Delay even numbered philosophers to prevent deadlock
    if (philo->id % 2 == 0)
        usleep(1000);

    while (!*philo->dead)
    {
        if (philo_eat(philo))
            break;
        if (philo_sleep(philo))
            break;
        if (philo_think(philo))
            break;
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