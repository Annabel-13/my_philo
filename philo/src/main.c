/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboichuk <hboichuk@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 09:01:18 by hboichuk          #+#    #+#             */
/*   Updated: 2023/02/18 21:07:11 by hboichuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/* Main. No, it's realy main. Basic error checking and malloc. */
int	main(int argc, char *argv[])
{
	t_table	*table;

	if (argc < 5 || argc > 6)
	{
		printf("Error! Wrong number of parameters given to the program!");
		return (0);
	}
	if (ft_atoi(argv[1]) > 200)
	{
		printf("Error! Too many philosophers to simulate!");
		return (0);
	}
	if (ft_atoi(argv[1]) < 0 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3]) < 0 || \
		ft_atoi(argv[4]) < 0 || (argc == 6 && ft_atoi(argv[5]) < 0))
	{
		printf("Error! Arguments can't be negative numbers!");
		return (0);
	}
	table = malloc(sizeof(t_table) * 1);
	if (init(argv, argc, table))
		return (-1);
	ending_check(table);
}
