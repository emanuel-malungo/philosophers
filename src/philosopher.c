/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:52:24 by emalungo          #+#    #+#             */
/*   Updated: 2024/10/21 14:44:35 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

int	main(int argc, char **argv)
{
	t_philosopher	*philo;

	philo = init_philo();
	if (!philo || !check_parse_args(argc, argv, philo))
	{
		printf("Invalid arguments.\n");
		free(philo);
		return (1);
	}
	free(philo);
	return (0);
}
