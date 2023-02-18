/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think_repeat.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <ddzuba@student.wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:35:52 by ddzuba            #+#    #+#             */
/*   Updated: 2023/01/13 17:30:11 by ddzuba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_philo(t_philo *philo)
{
	if (philo->num_of_philo == 1)
	{
		philo->ready_to_go = true;
		philo->start_time = get_timestamp();
	}
	while (philo->ready_to_go == false)
		usleep(1);
}

//differences: all actions in 1 function
int	philo_actions(t_philo	*all)
{
	sem_wait(all->fork);
	info_print(all, "has taken a fork");
	if (all->num_of_philo == 1)
		return (sem_post(all->fork), 1);
	sem_wait(all->fork);
	info_print(all, "has taken a fork");
	info_print(all, "is eating");
	all->when_last_eat = get_timestamp();
	ft_usleep(all->time_to_eat);
	sem_post(all->fork);
	sem_post(all->fork);
	all->num_must_eat++;
	info_print(all, "is sleeping");
	ft_usleep(all->time_to_sleep);
	info_print(all, "is thinking");
	return (0);
}

/* Checking status of each philo. If philo last eat counter bigger than  */
/* dying time, puts death flag and prints message */
void	*if_dead(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		if (philo->num_of_lunch)
			if (philo->num_must_eat == philo->num_of_lunch)
				break ;
		if (get_timestamp() - philo->when_last_eat > philo->time_to_die)
		{
			philo->flag_of_death = 1;
			sem_wait(philo->print);
			printf("%lld %d is died\n",
				get_timestamp() - philo->start_time, philo->name_of_philo);
			break ;
		}
	}
	if (philo->flag_of_death)
		exit (1);
	else
		exit (0);
}
