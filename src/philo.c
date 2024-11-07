/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:52:24 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/07 16:44:45 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_table			*table;
	t_philosopher	*philo;

	if (argc != 5 && argc != 6)
		return (0);
	table = init_table();
	if (!check_numbers(argc, argv, table))
	{
		printf("Invalid arguments.\n");
		free(table->forks);
		free(table);
		return (1);
	}
	philo = init_philo(table);
	if (!init(philo, table))
	{
		printf("Error initializing forks.\n");
		free_all(philo, table);
		return (1);
	}
	free_all(philo, table);
	return (0);
}
