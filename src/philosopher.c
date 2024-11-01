/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:52:24 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/01 14:40:02 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

t_philosopher	*init_philo(t_table *table)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)malloc(sizeof(t_philosopher) * table->n_philo);
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philosopher));
	return (philo);
}
t_table *init_table(void)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	table->start_time = get_time();
	table->is_alive = 1;
	table->print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table->print, NULL);
	return (table);
}



int	main(int argc, char **argv)
{
	t_table	*table;
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
		free(philo);
		return (1);
	}
	free(philo);
	return (0);
}
