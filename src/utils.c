/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 11:52:58 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/08 11:25:54 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Free allocated memory for philosophers and the table.
void	free_all(t_philosopher *philo, t_table *table)
{
	free(table->forks);
	free(table);
	free(philo);
}

// Check if a character is a digit.
static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

// Convert a string to an integer.
static int	ft_atoi(char *str)
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

// Check if the input arguments are valid numbers and assign them to the table.
int	check_numbers(int argc, char **argv, t_table *table)
{
	if (!check_parse_args(argc, argv))
		return (0);
	table->n_philo = ft_atoi(argv[1]);
	table->t_cat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	table->t_die = ft_atoi(argv[2]);
	table->n_times_eat = -1;
	if (argc == 6)
	{
		table->n_times_eat = ft_atoi(argv[5]);
		if (table->n_times_eat <= 0)
			return (0);
	}
	if (table->n_philo <= 0 || table->t_die <= 0
		|| table->t_cat <= 0 || table->t_sleep <= 0)
	{
		return (0);
	}
	return (1);
}

// Check if all arguments are digits.
int	check_parse_args(int argc, char **argv)
{
	int	i;
	int	j;

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
	return (1);
}
