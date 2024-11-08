/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:13:19 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/08 11:19:04 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Function to initialize the forks (mutexes) for the table.
int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->forks)
		return (0);
	while (i < table->n_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			free(table->forks);
			return (0);
		}
		i++;
	}
	return (1);
}

// Function to lock the forks for a philosopher.
void	get_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->rigth_fork]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->rigth_fork]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
	}
}

// Function to unlock the forks after use.
void	drop_forks(t_philosopher *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->rigth_fork]);
	}
	else
	{
		pthread_mutex_unlock(&philo->table->forks[philo->rigth_fork]);
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	}
}
