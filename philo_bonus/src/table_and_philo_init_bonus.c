/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_and_philo_init_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 15:13:41 by hboichuk          #+#    #+#             */
/*   Updated: 2023/02/08 18:24:51 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	int	print_init_error_with_free(char *str, t_philo *all)
{
	printf("%s", str);
	free(all);
	return (1);
}

//initialization of all params. Also we need right forks for 
// each philo, but only 1 left fork for two philos
t_philo	*initial_philosophers(int argc, char **argv)
{
	t_philo	*arg;

	arg = malloc(sizeof(t_philo));
	if (!arg)
	{
		printf("You can't allocate mem!");
		return (NULL);
	}
	arg->num_of_philo = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	arg->num_of_lunch = 0;
	arg->ready_to_go = true;
	if (argc == 6)
		arg->num_of_lunch = ft_atoi(argv[5]);
	arg->name_of_philo = 0;
	arg->start_time = 0;
	arg->flag_of_death = 0;
	arg->when_last_eat = 0;
	arg->num_must_eat = 0;
	return (arg);
}

//int sem_unlink(const char *name) - removes the named semaphore
//sem_open() creates a new POSIX semaphore or opens an existing semaphore,
//returns SEM_FAILED
int	init_sem_pid(t_philo *all)
{
	sem_unlink("print");
	sem_unlink("fork");
	all->print = sem_open("print", O_CREAT, 0644, 1);
	if (all->print == SEM_FAILED)
		return (print_init_error_with_free("Error: sem_print failed", all));
	all->fork = sem_open("fork", O_CREAT, 0644, all->num_of_philo);
	if (all->fork == SEM_FAILED)
		return (print_init_error_with_free("Error: sem_fork failed", all));
	all->pid = malloc(sizeof(pid_t) * all->num_of_philo);
	if (!all->pid)
	{
		sem_close(all->print);
		sem_close(all->fork);
		return (print_init_error_with_free("Error: pid failed", all));
	}
	return (0);
}
