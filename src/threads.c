/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:23:53 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/07 16:44:18 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_philosopher_death(t_philosopher *philo, t_table *table)
{
	long	time;

	time = get_time();
	if (time - philo->last_meal > table->t_die + 4)
	{
		print_status(philo, "died");
		pthread_mutex_lock(&table->alive_mutex);
		table->is_alive = 0;
		pthread_mutex_unlock(&table->alive_mutex);
		return (1);
	}
	return (0);
}

static int	check_all_philosophers(t_philosopher *philo, t_table *table)
{
	int	i;
	int	philo_done;

	i = 0;
	philo_done = 0;
	while (i < table->n_philo)
	{
		pthread_mutex_lock(&philo[i].eaten_mutex);
		if (philo[i].eaten >= table->n_times_eat)
		{
			if (philo[i].eaten >= table->n_times_eat table->n_times_eat != -1)
			{
				pthread_mutex_unlock(&philo[i].eaten_mutex);
				i++;
				philo_done++;
				continue ;
			}
		}
		pthread_mutex_unlock(&philo[i].eaten_mutex);
		pthread_mutex_lock(&table->alive_mutex);
		if (check_philosopher_death(&philo[i], table))
		{
			pthread_mutex_unlock(&table->alive_mutex);
			return (1);
		}
		pthread_mutex_unlock(&table->alive_mutex);
		usleep(100);
		i++;
	}
	if (philo_done == table->n_philo)
	{
		pthread_mutex_lock(&table->alive_mutex);
		table->is_alive = 0;
		pthread_mutex_unlock(&table->alive_mutex);
	}
	return (0);
}

void	*verify_death(void *arg)
{
	t_table			*table;
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	table = philo->table;
	while (1)
	{
		if (check_all_philosophers(philo, table))
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

void	*simulation(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->table->n_philo == 1)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		print_status(philo, "has taken a fork");
		while (1)
		{
			if (philo->table->is_alive != 1)
				break ;
		}
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
