/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:02:56 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/07 15:50:04 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philosopher	*init_philo(t_table *table)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)malloc(sizeof(t_philosopher) * table->n_philo);
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philosopher));
	return (philo);
}

t_table	*init_table(void)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	table->start_time = get_time();
	table->is_alive = 1;
	pthread_mutex_init(&table->print, NULL);
	return (table);
}

int	init(t_philosopher *philo, t_table *table)
{
	int	i;

	if (!init_forks(table))
		return (0);
	i = -1;
	while (++i < table->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].eaten = 0;
		philo[i].left_fork = i;
		philo[i].rigth_fork = (i + 1) % table->n_philo;
		philo[i].table = table;
		philo[i].last_meal = get_time();
		pthread_mutex_init(&philo[i].eaten_mutex, NULL);
	}
	i = -1;
	while (++i < table->n_philo)
		pthread_create(&philo[i].thread, NULL, simulation, &philo[i]);
	pthread_create(&philo->death_thread, NULL, verify_death, philo);
	i = -1;
	while (++i < table->n_philo)
		pthread_join(philo[i].thread, NULL);
	pthread_join(philo->death_thread, NULL);
	return (1);
}
