/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboichuk <hboichuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:01:16 by hboichuk          #+#    #+#             */
/*   Updated: 2023/02/18 19:02:46 by hboichuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	ft_atoi(const char *str)
{
	int					i;
	int					flag;
	unsigned long long	nbr;

	i = 0;
	nbr = 0;
	flag = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-')
		flag = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (-1);
	if (flag == 1 && nbr >= 9223372036854775807u)
		return (-1);
	if (flag == -1 && nbr >= 9223372036854775808u)
		return (0);
	return (nbr * flag);
}

/* Just free all the memory data */
//sem_unlink - turn off the semaphore
void	ft_free(t_philo *all)
{
	sem_unlink("print");
	sem_unlink("fork");
	sem_close(all->print);
	sem_close(all->fork);
	free(all->pid);
	free(all);
}

/* Just for printing actual info about philo - philo start time, id, message */
/*sem_post () увеличивает (разблокирует) семафор, на который указывает sem. 
    Если значение семафора становится больше нуля, 
    тогда другой процесс или поток, заблокированный вызовом sem_wait(3),будет 
    разбужен и продолжит блокировку семафора.*/
void	info_print(t_philo *philo, char *str)
{
	sem_wait(philo->print);
	printf("%lld %d %s\n",
		get_timestamp() - philo->start_time, philo->name_of_philo, str);
	sem_post(philo->print);
}

// ◦ timestamp_in_ms X has taken a fork
// ◦ timestamp_in_ms X is eating
// ◦ timestamp_in_ms X is sleeping
// ◦ timestamp_in_ms X is thinking
// ◦ timestamp_in_ms X died

/* Taking time from system. t.tv_sec - in seconds, t.tv_usec - microseconds */
long long	get_timestamp(void)
{
	struct timeval	t;
	long long		now;

	gettimeofday(&t, NULL);
	now = ((t.tv_sec * 1000) + (t.tv_usec / 1000));
	return (now);
}

/* Sleep function for philo actions, like "sleep", "eat" etc */
void	ft_usleep(long long time)
{
	long long	start;

	start = get_timestamp();
	while (get_timestamp() - start < time)
		usleep(100);
}
