/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:23:53 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/14 09:50:21 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Check if a philosopher has died.
static int	check_philosopher_death(t_philosopher *philo, t_table *table)
{
	long	time;

	time = get_time();
	if (time - philo->last_meal > table->t_die + 4)
	{
		print_status(philo, "died");
		table->is_alive = 0;
		return (1);
	}
	return (0);
}

// Check if any philosopher died
static int	is_philosopher_dead(t_philosopher *philo, t_table *table)
{
	pthread_mutex_lock(&table->alive_mutex);
	if (check_philosopher_death(philo, table))
	{
		pthread_mutex_unlock(&table->alive_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->alive_mutex);
	return (0);
}

// Check if any philosopher is still alive.
static int	check_philosophers_alive(t_philosopher *philo,
		t_table *table, int philo_done)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (has_philosopher_eaten_enough(&philo[i], table))
		{
			philo_done++;
			i++;
			continue ;
		}
		if (is_philosopher_dead(&philo[i], table))
			return (1);
		usleep(100);
		i++;
	}
	if (philo_done == table->n_philo)
	{
		pthread_mutex_lock(&table->alive_mutex);
		table->is_alive = 0;
		pthread_mutex_unlock(&table->alive_mutex);
		return (1);
	}
	return (0);
}

// Thread function to check death or meal completion.
void	*verify_death(void *arg)
{
	t_table			*table;
	int				philo_done;
	t_philosopher	*philo;

	philo_done = 0;
	philo = (t_philosopher *)arg;
	table = philo->table;
	while (1)
	{
		if (check_philosophers_alive(philo, table, philo_done))
			return (NULL);
		pthread_mutex_lock(&table->alive_mutex);
		if (!table->is_alive)
		{
			pthread_mutex_unlock(&table->alive_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->alive_mutex);
	}
	return (NULL);
}

// Philosopher's main simulation loop.
void	*simulation(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->table->n_philo == 1)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		usleep(philo->table->t_die * 1000);
		pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
		return (NULL);
	}
	while (1)
	{
		if (!philosopher_routine(philo))
			break ;
	}
	return (NULL);
}
