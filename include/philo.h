/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:42:22 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/07 15:59:07 by emalungo         ###   ########.fr       */
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
	 int		is_alive;
	int				n_times_eat;
	long			start_time;
	pthread_t		destroy_philo;
	pthread_mutex_t	print;
	pthread_mutex_t	alive_mutex;
	pthread_mutex_t	*forks;
	int		finished_eating_count;
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
	pthread_mutex_t eaten_mutex;
}				t_philosopher;

//	./src/utils.c
int		check_parse_args(int argc, char **argv);
void	free_all(t_philosopher *philo, t_table *table);
int		check_numbers(int argc, char **argv, t_table *table);

//	./src/init.c
t_philosopher	*init_philo(t_table *table);
t_table	*init_table(void);
int		init(t_philosopher *philo, t_table *table);

//	./src/threads.c
void	*simulation(void *arg);
void	*verify_death(void *arg);

//	./src/routine.c
long	get_time(void);
int		philosopher_routine(t_philosopher *philo);
void	print_status(t_philosopher *philo, char *status);

//	./src/forks.c
int		init_forks(t_table *table);
void	get_forks(t_philosopher *philo);
void	drop_forks(t_philosopher *philo);

#endif
