#include "philo.h"

void cleanup_program(t_program *program)
{
    int i;
    int num_philos;

	i = 0;
    num_philos = program->philos[0].num_of_philos;
    while(i < num_philos)
        pthread_mutex_destroy(&program->forks[i++]);
    pthread_mutex_destroy(&program->dead_lock);
    pthread_mutex_destroy(&program->meal_lock);
    pthread_mutex_destroy(&program->write_lock);
} 