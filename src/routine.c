/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:38:57 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/07 16:06:29 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_status(t_philosopher *philo, char *status)
{
	pthread_mutex_lock(&philo->table->alive_mutex);
	if (philo->table->is_alive != 0)
	{
		pthread_mutex_lock(&philo->table->print);
		printf("%ld %d %s\n", get_time() - philo->table->start_time,
			philo->id, status);
		pthread_mutex_unlock(&philo->table->print);
	}
	pthread_mutex_unlock(&philo->table->alive_mutex);
}

long	get_time(void)
{
	struct timeval	time;
	long			ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

int	eat_routine(t_philosopher *philo, int *meals_count)
{
	get_forks(philo);
	pthread_mutex_lock(&philo->table->alive_mutex);
	if (!philo->table->is_alive)
	{
		pthread_mutex_unlock(&philo->table->alive_mutex);
		drop_forks(philo);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->alive_mutex);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->table->alive_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->alive_mutex);
	usleep(philo->table->t_cat * 1000);
	(*meals_count)++;
	pthread_mutex_lock(&philo->eaten_mutex);
	philo->eaten++;
	pthread_mutex_unlock(&philo->eaten_mutex);
	drop_forks(philo);
	return (1);
}

int	check_meals(t_philosopher *philo, int meals_needed, int meals_count)
{
	if (meals_needed != -1 && meals_count >= meals_needed)
	{
		pthread_mutex_lock(&philo->table->alive_mutex);
		philo->table->finished_eating_count++;
		if (philo->table->finished_eating_count == philo->table->n_philo)
		{
			philo->table->is_alive = 2;
		}
		pthread_mutex_unlock(&philo->table->alive_mutex);
		return (0);
	}
	return (1);
}

int	philosopher_routine(t_philosopher *philo)
{
	int	meals_needed;
	int	meals_count;

	meals_count = 0;
	meals_needed = philo->table->n_times_eat;
	while (1)
	{
		if (!eat_routine(philo, &meals_count))
			return (0);
		print_status(philo, "is sleeping");
		usleep(philo->table->t_sleep * 1000);
		print_status(philo, "is thinking");
		if (!check_meals(philo, meals_needed, meals_count))
			return (0);
	}
}
