#include "philo.h"

int	ft_isdigit(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] < '0' || str[i] > '9')
			return(1);
		i++;
	}
	return(0);
}

int check_only_num(char **argv)
{
	int i;
	int digit;

	digit = 0;
	i = 1;
	while(argv[i])
	{
		if(ft_isdigit(argv[i]) == 1)
			return(1);
		i++;
	}
	return 0;
}
/*
argv[1] = number_of_philosophers (1-200)
argv[2] = time_to_die (in milliseconds)
argv[3] = time_to_eat (in milliseconds)
argv[4] = time_to_sleep (in milliseconds)
argv[5] = [optional] number_of_times_each_philosopher_must_eat
*/


int check_value_ranges(char **argv)
{
	int i;
	int value;

	i = 1;
	while(argv[i])
	{
		value = ft_atoi(argv[i]);
		if(i == 1 && value > 200)
		{
			printf("max 200 philo\n");
			return(1);
		}
		if(value <= 0)
		{
			printf("arg %d to small\n", i);
			return(1);
		}
		i++;
	}
	return(0);
}

int check_args(int argc, char **argv)
{
	if(argc != 5 && argc != 6)
	{
		printf("not anoug arg\n");
		return(1);
	}
	if(check_only_num(argv) == 1)
	{
		printf("is not a digit\n");
		return(1);
	}
	if(check_value_ranges(argv) == 1)
		return(1);
	return(0);
}