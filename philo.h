#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	forks[200];
	t_philo			*philos;
}					t_program;

/* check_args.c */
int		check_args(int argc, char **argv);
int		ft_isdigit(char *str);
int		check_only_num(char **argv);
int		check_value_ranges(char **argv);

/* init.c */
int		init_all(int argc, char **argv, t_program *program);

/* utils.c */
int		ft_atoi(const char *nptr);
size_t	get_current_time(void);
void	print_status(t_philo *philo, char *status);
int		ft_usleep(size_t milliseconds);

/* program.c */
int		create_program(t_program *program);
void	*philosopher_routine(void *arg);

/* actions.c */
int		philo_eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		philo_think(t_philo *philo);

/* monitor.c */
void	*death_monitor(void *arg);

/* cleanup.c */
void	cleanup_program(t_program *program);

#endif