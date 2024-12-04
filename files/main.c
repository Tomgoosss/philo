/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:03:14 by tgoossen          #+#    #+#             */
/*   Updated: 2024/12/04 15:32:32 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_program	program;

	if (check_args(argc, argv))
		return (1);
	program.philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	if (!program.philos)
		return (1);
	if (init_all(argc, argv, &program))
	{
		free(program.philos);
		return (1);
	}
	if (create_program(&program))
	{
		free(program.philos);
		return (1);
	}
	cleanup_program(&program);
	free(program.philos);
	return (0);
}
