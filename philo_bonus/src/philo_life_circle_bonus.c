/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_circle_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:09:18 by ddzuba            #+#    #+#             */
/*   Updated: 2023/02/08 18:23:25 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_life_circle(t_philo *all)
{
	check_philo(all);
	if (pthread_create(&all->thread_for_death, NULL, &if_dead, all))
	{
		printf("Fail with pthread_create");
		return (1);
	}
	if (all->name_of_philo % 2 == 1)
		usleep(500);
	while (1)
	{
		if (all->num_of_lunch)
			if (all->num_must_eat == all->num_of_lunch)
				break ;
		if (philo_actions(all))
			break ;
	}
	if (pthread_join(all->thread_for_death, NULL))
	{
		printf("Fail with pthread_join");
		return (1);
	}
	return (0);
}

int	kill_philo(t_philo	*all)
{
	int	i;

	i = -1;
	while (++i < all->num_of_philo)
		kill(all->pid[i], SIGKILL);
	return (0);
}
