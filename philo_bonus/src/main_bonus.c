/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboichuk <hboichuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 20:05:45 by hboichuk          #+#    #+#             */
/*   Updated: 2023/02/02 19:09:15 by hboichuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/* Cheking arguments. It must be 5 or 6 args, bigger than 0, and not more */
/* 200 philosophers (according to checklist) */
int	cheking_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("ERROR: Wrong number of arguments!\n");
		return (1);
	}
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0
		|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0
		|| (argc == 6 && ft_atoi(argv[5]) <= 0))
	{
		printf("ERROR: Wrong arguments!\n");
		return (1);
	}
	if (ft_atoi(argv[1]) >= 201)
	{
		printf("ERROR: Do not use more than 200 philo!");
		return (1);
	}
	return (0);
}

//WEXITSTATUS–Obtain exit status of a child process
int	start_game(t_philo *all)
{
	int	i;
	int	status;

	i = -1;
	all->start_time = get_timestamp();
	while (++i < all->num_of_philo)
	{
		all->pid[i] = fork();
		if (all->pid[i] == -1)
		{
			printf("fail with fork");
			return (1);
		}
		if (all->pid[i] == 0)
		{
			all->name_of_philo = i + 1;
			all->when_last_eat = all->start_time;
			if (philo_life_circle(all))
				return (0);
		}
	}
	while (waitpid(-1, &status, 0) > 0)
		if (WEXITSTATUS(status) == 1)
			return (kill_philo(all));
	return (0);
}

// ◦ number_of_philosophers
// ◦ time_to_die (in milliseconds)
// ◦ time_to_eat (in milliseconds)
// ◦ time_to_sleep (in milliseconds)
// ◦ number_of_times_each_philosopher_must_eat (optional argument)
int	main(int argc, char **argv)
{
	t_philo	*all;

	if (cheking_args(argc, argv))
		return (1);
	all = initial_philosophers(argc, argv);
	if (init_sem_pid(all))
		return (1);
	if (start_game(all))
		return (1);
	ft_free(all);
	return (0);
}
