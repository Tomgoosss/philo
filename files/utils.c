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

size_t get_current_time(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL) == -1)
        return (0);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void print_status(t_philo *philo, char *status)
{
    pthread_mutex_lock(philo->write_lock);
    printf("%zu %d %s\n", get_current_time() - philo->start_time, philo->id, status);
    pthread_mutex_unlock(philo->write_lock);
}

int ft_usleep(size_t milliseconds)
{
    size_t start;

    start = get_current_time();
    while ((get_current_time() - start) < milliseconds)
        usleep(500);
    return (0);
}