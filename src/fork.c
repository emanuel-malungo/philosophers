/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:13:19 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/14 09:11:21 by emalungo         ###   ########.fr       */
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

// Check if a philosopher has eaten enough times
int	has_philosopher_eaten_enough(t_philosopher *philo, t_table *table)
{
	pthread_mutex_lock(&philo->eaten_mutex);
	if (philo->eaten >= table->n_times_eat && table->n_times_eat != -1)
	{
		pthread_mutex_unlock(&philo->eaten_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->eaten_mutex);
	return (0);
}
