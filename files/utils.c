#include <philo.h>

int	ft_atoi(const char *nptr)
{
	int			i;
	int			r;
	long long	result;

	i = 0;
	r = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
		r = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (result < 0 && r == -1)
			return (0);
		if (result < 0 && r == 1)
			return (-1);
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	return (r * result);
}