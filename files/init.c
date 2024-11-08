#include "philo.h"

void init_struct(int argc, char **argv, t_program *program)
{
	program->philos->num_of_philos = ft_atoi(argv[1]);
	program->philos->time_to_die = ft_atoi(argv[2]);
	program->philos->time_to_eat = ft_atoi(argv[3]);
	program->philos->time_to_sleep = ft_atoi(argv[4]);
	if(argc == 6)
		program->philos->num_times_to_eat = ft_atoi(argv[5]);
}

int init_all(int argc, char **argv, t_program *program)
{
	init_struct(argc, argv, program);
	return(0);
}