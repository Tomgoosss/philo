#include "philo.h"

int main(int argc, char **argv)
{
	t_program *program;

	program = malloc(sizeof(t_program));
	if (!program)
        return (1);
	program->philos = malloc(sizeof(t_philo));
	if (!program->philos)
	{
		free(program);
		return (1);
	}
	if(check_args(argc, argv) == 1)
	{
		printf("check args wrong\n");
		free(program->philos);
		free(program);
		return(0);
	}
	if(init_all(argc, argv, program) == 1)
	{
		printf("error init\n");
		//clean up all
		free(program->philos);
		free(program);
		return(1);
	}
	return(0);
}