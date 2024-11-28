#include "philo.h"

static int check_all_ate(t_program *program)
{
    int i;
    int finished_eating;

    if (program->philos[0].num_times_to_eat == -1)
        return (0);
    i = 0;
    finished_eating = 0;
    pthread_mutex_lock(&program->meal_lock);
    while (i < program->philos[0].num_of_philos)
    {
        if (program->philos[i].meals_eaten >= program->philos[i].num_times_to_eat)
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

void *death_monitor(void *arg)
{
    t_program *program;
    int i;
    size_t time;

    program = (t_program *)arg;
    while (1)
    {
        i = 0;
        while (i < program->philos[0].num_of_philos)
        {
            pthread_mutex_lock(&program->meal_lock);
            time = get_current_time() - program->philos[i].last_meal;
            if (!program->philos[i].eating && time >= program->philos[i].time_to_die)
            {
                print_status(&program->philos[i], "died");
                pthread_mutex_lock(&program->dead_lock);
                program->dead_flag = 1;
                pthread_mutex_unlock(&program->dead_lock);
                pthread_mutex_unlock(&program->meal_lock);
                return (NULL);
            }
            pthread_mutex_unlock(&program->meal_lock);
            if (check_all_ate(program))
                return (NULL);
            i++;
        }
        usleep(100);
    }
    return (NULL);
} 
