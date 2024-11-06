/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:42:22 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/06 15:57:34 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_table
{
	int				t_die;
	int				t_cat;
	int				t_sleep;
	int				n_philo;
	_Atomic int		is_alive;
	int				n_times_eat;
	long			start_time;
	pthread_t		destroy_philo;
	pthread_mutex_t	*print;
	pthread_mutex_t	alive_mutex;
	pthread_mutex_t	*forks;
	_Atomic int		finished_eating_count;
}				t_table;

typedef struct s_philosopher
{
	int				id;
	int				eaten;
	long			last_meal;
	int				left_fork;
	int				rigth_fork;
	pthread_t		thread;
	t_table			*table;
	pthread_t		death_thread;
}				t_philosopher;

//	./src/utils.c
long	get_time(void);
int		check_parse_args(int argc, char **argv);
int		check_numbers(int argc, char **argv, t_table *table);

//	./src/init.c
t_table	*init_table(void);
t_philosopher	*init_philo(t_table *table);
int		init(t_philosopher *philo, t_table *table);

//	./src/threads.c
void	*simulation(void *arg);
void	*verify_death(void *arg);

//	./src/routine.c
int		philosopher_routine(t_philosopher *philo);
void	print_status(t_philosopher *philo, char *status);

//	./src/forks.c
int		init_forks(t_table *table);
void	get_forks(t_philosopher *philo);
void	drop_forks(t_philosopher *philo);

#endif
