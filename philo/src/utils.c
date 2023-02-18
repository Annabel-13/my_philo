/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboichuk <hboichuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 09:45:44 by hboichuk          #+#    #+#             */
/*   Updated: 2023/02/18 20:54:38 by hboichuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* Part of ft_atoi */
static int	check_minus(const char *str, int *num)
{
	while (str[*num] >= 0 && (str[*num] == 32 || str[*num] == '\t'
			|| str[*num] == '\n' || str[*num] == '\r'
			|| str[*num] == '\v' || str[*num] == '\f'))
	{
		++*num;
	}
	if (str[*num] == '-')
	{
		++*num;
		return (1);
	}
	else if (str[*num] == '+')
	{
		++*num;
		return (0);
	}
	return (0);
}

/* atoi. Well, needs for puting arguments as int */
int	ft_atoi(const char *str)
{
	int	a;
	int	num;
	int	b;

	a = 0;
	num = 0;
	b = check_minus(str, &num);
	while (str[num] != '\0')
	{
		if (str[num] > '9' || str[num] < '0')
		{
			break ;
		}
		a = (a * 10) + (str[num] - '0');
		++num;
	}
	if (b == 1)
	{
		a = (-1) * a;
	}
	return (a);
}

/* Part of printing */
void	print_death(t_philo *philo, t_table *table, size_t n)
{
	printf("\x1B[35m%zu ", diff(c_time(), philo->table->start));
	printf("\x1B[35m%zu ", table->philo[n].number);
	printf("\x1B[35m%s", "died\n");
}

/* Prints all information on screen. Also checks the dead of philo */
void	print_output(t_philo *philo, char *message)
{
	t_table	*table;
	int		n;

	pthread_mutex_lock(&philo->table->write);
	table = philo->table;
	n = table->num_of_philo;
	while (n > 0 && table->philo[n].number)
	{
		if (diff(c_time(), table->philo[n].lst_meal) >= \
			philo->table->time_to_die && philo->table->is_dead)
		{
			philo->table->is_dead = 0;
			print_death(philo, table, n);
			pthread_mutex_unlock(&philo->table->write);
			return ;
		}
		n--;
	}
	if (philo->table->is_dead)
	{
		printf("\033[1;34m%zu ", diff(c_time(), philo->table->start));
		printf("\033[1;33m%zu ", philo->number);
		printf("\033[1;32m%s\n", message);
	}
	pthread_mutex_unlock(&philo->table->write);
}

/* Little improvement for "current time". Needs for correct work */
void	sleep_for_given_time(size_t time)
{
	unsigned long long	i;

	i = c_time();
	while (1)
	{
		if (diff(c_time(), i) >= time)
			break ;
	}
}
