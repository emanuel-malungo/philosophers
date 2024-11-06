/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:52:24 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/06 14:25:19 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_all(t_philosopher *philo, t_table *table)
{
	free(table->print);
	free(table->forks);
	free(table);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_table			*table;
	t_philosopher	*philo;

	if (argc != 5 && argc != 6)
		return (0);
	table = init_table();
	if (!check_numbers(argc, argv, table))
		return (0);
	philo = init_philo(table);
	if (!philo || !check_parse_args(argc, argv))
	{
		printf("Invalid arguments.\n");
		free(philo);
		return (1);
	}
	if (!init(philo, table))
	{
		printf("Error initializing forks.\n");
		free(table);
		free(philo);
		return (1);
	}
	free_all(philo, table);
	return (0);
}
