/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboichuk <hboichuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:56:44 by hboichuk          #+#    #+#             */
/*   Updated: 2023/02/18 18:56:39 by hboichuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* Check status of philos. Waits until all philo will be ready to go */
void	check_philo(t_philo *philo, t_table *table)
{
	if (philo->number == 1)
	{
		table->philos_ready = true;
		table->start = c_time();
	}
	while (table->philos_ready == false)
		usleep(1);
}

/* Philos algorithm. Eat, sleep, think. */
void	*philosophers(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	check_philo(philo, table);
	if (table->num_of_philo == 1)
	{
		sleep_for_given_time(table->time_to_die);
		print_output(philo, "died");
		return (NULL);
	}
	if (philo->number % 2)
		usleep(table->time_to_eat * 1000);
	while (table->is_dead)
	{
		meal(philo);
		if (philo->meal_times == table->num_of_meals)
			break ;
		print_output(philo, "is sleeping");
		sleep_for_given_time(table->time_to_sleep);
		print_output(philo, "is thinking");
	}
	return (NULL);
}
