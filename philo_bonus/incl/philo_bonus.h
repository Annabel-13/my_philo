/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddzuba <hboichuk@student.wolfsburg.de>       +#+  +:+       +#+      */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:55:43 by hboichuk            #+#    #+#           */
/*   Updated: 2022/12/29 16:55:43 by hboichuk           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h> 
# include <stdio.h> 
# include <string.h> 
# include <stdlib.h> 
# include <sys/time.h> 
# include <pthread.h> 
# include <semaphore.h> 
# include <signal.h>
# include <sys/wait.h> 
# include <stdbool.h>

/* Diference: philosophers and table data in one struct.We don't need 2struct */
// fork - pointer on semaphore for forks

typedef struct s_philo
{
	int				num_of_philo;
	int				name_of_philo;
	pid_t			*pid;
	int				time_to_sleep;
	int				time_to_eat;
	int				time_to_die;
	int				num_of_lunch;
	long long		start_time;
	long long		when_last_eat;
	int				num_must_eat;
	int				flag_of_death;
	pthread_t		thread_for_death;
	sem_t			*fork;
	sem_t			*print;
	bool			ready_to_go;

}		t_philo;

/*						List of functions						*/

/*						Utility functions						*/

long long	get_timestamp(void);
long long	ft_atoi(const char *str);
void		ft_free(t_philo *all);
void		ft_usleep(long long time);
void		info_print(t_philo *philo, char *str);

/*						Initialization functions				*/
t_philo		*initial_philosophers(int argc, char **argv);

/*						Errors managment						*/

int			cheking_args(int argc, char **argv);
void		check_philo(t_philo *philo);

/*						General functions						*/
int			philo_actions(t_philo *all);
void		*if_dead(void *data);
int			start_game(t_philo *all);
int			init_sem_pid(t_philo *all);
int			kill_philo(t_philo	*all);
int			philo_life_circle(t_philo *all);
#endif
