/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboichuk <hboichuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:11:59 by hboichuk          #+#    #+#             */
/*   Updated: 2023/02/18 20:54:53 by hboichuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>

/* Philo main table. Tied to each philo */
typedef struct s_philo
{
	size_t			lst_meal;
	size_t			left_hand;
	size_t			right_hand;
	pthread_t		tread;
	size_t			number;
	size_t			meal_times;
	struct s_table	*table;
}				t_philo;

/* Table structure whats keep all information about programm */
typedef struct s_table
{
	size_t				start;
	pthread_mutex_t		fork[200];
	pthread_mutex_t		write;
	t_philo				philo[200];
	size_t				is_dead;
	size_t				num_of_meals;
	size_t				num_of_philo;
	size_t				time_to_die;
	size_t				time_to_sleep;
	size_t				time_to_eat;
	bool				philos_ready;
}			t_table;

size_t	c_time(void);
void	meal(t_philo *philo);
void	*philosophers(void *arg);
int		ft_atoi(const char *str);
size_t	init(char *argv[], size_t argc, t_table *table);
void	exit_function(size_t n, t_table *table);
void	destroy(size_t n, t_table *table);
void	print_output(t_philo *philo, char *message);
void	ending_check(t_table *table);
size_t	diff(size_t pre, size_t post);
void	sleep_for_given_time(size_t time);

#endif
