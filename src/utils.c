/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:52:58 by emalungo          #+#    #+#             */
/*   Updated: 2024/10/21 15:03:19 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sig;
	int	res;

	i = 0;
	sig = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] > 9 && str[i] < 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sig = -1;
		str++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sig);
}

t_philosopher	*init_philo(void)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!philo)
		return (NULL);
	philo->t_cat = 0;
	philo->t_die = 0;
	philo->t_sleep = 0;
	philo->n_philo = 0;
	philo->n_times_eat = 0;
	return (philo);
}

int	check_numbers(char **argv, t_philosopher *philo)
{
	philo->n_philo = ft_atoi(argv[1]);
	philo->t_die = ft_atoi(argv[2]);
	philo->t_cat = ft_atoi(argv[3]);
	philo->t_sleep = ft_atoi(argv[4]);
	philo->n_times_eat = ft_atoi(argv[5]);
	printf("%d", philo->n_times_eat);
	if (philo->n_philo <= 0 || philo->t_die <= 0
		|| philo->t_cat <= 0 || philo->t_sleep <= 0
		|| philo->n_times_eat <= 0)
	{
		return (0);
	}
	return (1);
}

int	check_parse_args(int argc, char **argv, t_philosopher *philo)
{
	int	i;
	int	j;

	if (argc != 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	if (!check_numbers(argv, philo))
	{
		return (0);
	}	
	return (1);
}
