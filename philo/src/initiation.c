/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboichuk <hboichuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:45:59 by hboichuk          #+#    #+#             */
/*   Updated: 2023/02/18 18:55:42 by hboichuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* Initialization of each philo with starting arguments */
void	init_philosophers(size_t n, t_table *table)
{
	table->is_dead = 1;
	table->philo[n].number = n;
	table->philo[n].meal_times = 0;
	table->philo[n].left_hand = n;
	table->philo[n].right_hand = 1;
	table->philo[n].table = table;
	n--;
	while (n > 0)
	{
		table->philo[n].number = n;
		table->philo[n].meal_times = 0;
		table->philo[n].left_hand = n;
		table->philo[n].right_hand = (n + 1);
		table->philo[n].table = table;
		n--;
	}
}

/* "Fork" initialization */
size_t	init_fork(size_t n, t_table *table)
{
	while (n > 0)
	{
		if (pthread_mutex_init(&table->fork[n], NULL))
			return (0);
		n--;
	}
	if (pthread_mutex_init(&table->write, NULL))
		return (0);
	return (1);
}

/* Each philo must be as separate thread. Creates threads. */
size_t	init_philo(size_t n, t_table *table)
{
	table->start = c_time();
	while (n > 0)
	{
		if (pthread_create(&table->philo[n].tread, NULL, \
			&philosophers, &table->philo[n]))
			return (0);
		table->philo[n].lst_meal = c_time();
		n--;
	}
	table->philos_ready = true;
	return (1);
}

/* Initialization according to input parameters */
size_t	init(char *argv[], size_t argc, t_table *table)
{
	table->num_of_philo = ft_atoi(argv[1]);
	if (table->num_of_philo <= 0)
		return (3);
	table->time_to_die = ft_atoi(argv[2]);
	if (table->time_to_die <= 0)
		return (4);
	table->time_to_eat = ft_atoi(argv[3]);
	if (table->time_to_eat <= 0)
		return (5);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (table->time_to_sleep <= 0)
		return (6);
	if (argc == 6)
		table->num_of_meals = ft_atoi(argv[5]);
	else
		table->num_of_meals = -1;
	if (!init_fork(table->num_of_philo, table))
		return (1);
	init_philosophers(table->num_of_philo, table);
	if (!init_philo(table->num_of_philo, table))
		return (2);
	return (0);
}
