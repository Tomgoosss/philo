#include "philo.h"

int main(int argc, char **argv)
{
	t_program program;

	// Check arguments
	if (check_args(argc, argv))
		return (1);

	// Allocate memory for philosophers
	program.philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!program.philos)
		return (1);

	// Initialize program and philosophers
	if (init_all(argc, argv, &program))
	{
		free(program.philos);
		return (1);
	}

	// Create and run philosopher threads
	if (create_program(&program))
	{
		free(program.philos);
		return (1);
	}

	// Cleanup mutexes and free memory
	cleanup_program(&program);
	free(program.philos);

	return (0);
}