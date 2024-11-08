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
	return(0);
}