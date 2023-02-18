/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboichuk <hboichuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 13:14:05 by hboichuk          #+#    #+#             */
/*   Updated: 2023/02/18 18:54:06 by hboichuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* Join all philo threads on exit */
void	exit_function(size_t n, t_table *table)
{
	size_t	i;

	i = 0;
	while (i <= n)
	{
		pthread_join(table->philo[n].tread, NULL);
		i++;
	}
}

/* Detach and destroys all mutex */
void	destroy(size_t n, t_table *table)
{
	size_t	i;

	i = 0;
	while (i <= n)
	{
		pthread_detach(table->philo[n].tread);
		pthread_mutex_destroy(&table->fork[n]);
		i++;
	}
	pthread_mutex_destroy(&table->write);
}

/* Clear exit with all previous functions */
void	ending_check(t_table *table)
{
	exit_function(table->num_of_philo, table);
	destroy(table->num_of_philo, table);
	free(table);
}
