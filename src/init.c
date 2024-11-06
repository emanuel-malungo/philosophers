/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:02:56 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/06 11:44:52 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	check_philosopher_death(t_philosopher *philo, t_table *table)
{
	long	time;

	time = get_time();
	if (philo->table->n_times_eat != -1)
	{
		if (time - philo->last_meal
			> table->t_die && philo->eaten
			< table->n_times_eat)
		{
			print_status(philo, "died");
			table->is_alive = 0;
			return (1);
		}
	}
	if (time - philo->last_meal > table->t_die + 4)
	{
		print_status(philo, "died");
		table->is_alive = 0;
		return (1);
	}
	return (0);
}

void	*verify_death(void *arg)
{
	t_table				*table;
	t_philosopher		*philo;
	int					i;

	philo = (t_philosopher *)arg;
	table = philo->table;
	while (1)
	{
		i = 0;
		while (i < table->n_philo)
		{
			pthread_mutex_lock(&table->alive_mutex);
			if (check_philosopher_death(&philo[i], table))
			{
				pthread_mutex_unlock(&table->alive_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&table->alive_mutex);
			usleep(100);
			i++;
		}
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
