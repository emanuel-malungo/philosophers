/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:42:22 by emalungo          #+#    #+#             */
/*   Updated: 2024/10/21 14:50:39 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philosopher
{
	int	n_philo;
	int	t_die;
	int	t_cat;
	int	t_sleep;
	int	n_times_eat;
}				t_philosopher;

// ./src/utils.c
//
t_philosopher	*init_philo(void);
int				check_parse_args(int argc, char **argv, t_philosopher *philo);

#endif
