#include "philo.h"


int main(int argc, char **argv)
{
	t_program program;
	pthread_mutex_t	philos[200];

	program.philos = philos;
	if(check_args(argc, argv) == 1)
	{
		// printf("check args wrong\n");
		return(0);
	}
	if(init_all(argc, argv, &program) == 1)
	{
		printf("error init\n");
		return(1);
	}
	// if(create_program(&program) == 1)
	// {
	// 	printf("some went wrong creating threads\n");
	// 	return(1);
	// }
	return(0);
}