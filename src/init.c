/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:02:56 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/01 15:23:20 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void	*verify_death(void *arg)
{
	t_philosopher	*philo;
	long			time;

	philo = (t_philosopher *)arg;
	while (philo->table->is_alive)
	{
		usleep(100);
        // pthread_mutex_lock(&philo->table->alive_mutex);
        time = get_time();
        if (time - philo->last_meal > philo->table->t_die)
        {
            print_status(philo, "died");
            philo->table->is_alive = 0;
            break ;
        }
        // pthread_mutex_unlock(&philo->table->alive_mutex);
        // printf("\nid %d %ld\n", philo->id, get_time() - philo->last_meal);
		usleep(100);
	}
	return (NULL);
}

void	print_status(t_philosopher *philo, char *status)
{
    pthread_mutex_lock(philo->table->print);
    if (philo->table->is_alive != 0)
	{
        printf("%ld %d %s\n", get_time() - philo->table->start_time, philo->id, status);
    }
    pthread_mutex_unlock(philo->table->print);
}

void	routine(t_philosopher *philo)
{
	get_forks(philo);
    print_status(philo, "is eating");
    philo->last_meal = get_time();
    usleep(philo->table->t_cat * 1e3);
    drop_forks(philo);
    print_status(philo, "is sleeping");
    usleep(philo->table->t_sleep * 1e3);
    print_status(philo, "is thinking");
}



void	*simulation(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
    // while (philo->table->is_alive)
    // {
        // routine(philo);
        while (1)
        {
            get_forks(philo);
            
            // Verificação de morte antes de comer
            pthread_mutex_lock(&philo->table->alive_mutex);
            if (!philo->table->is_alive)
            {
                pthread_mutex_unlock(&philo->table->alive_mutex);
                drop_forks(philo);
                break;
            }
            pthread_mutex_unlock(&philo->table->alive_mutex);

            print_status(philo, "is eating");
            
            // Atualiza o tempo da última refeição
            pthread_mutex_lock(&philo->table->alive_mutex);
            philo->last_meal = get_time();
            pthread_mutex_unlock(&philo->table->alive_mutex);
            
            usleep(philo->table->t_cat * 1000);  // Tempo de comer
            drop_forks(philo);
            
            // Verificação de morte após comer
            pthread_mutex_lock(&philo->table->alive_mutex);
            if (get_time() - philo->last_meal > philo->table->t_die)
            {
                print_status(philo, "died");
                philo->table->is_alive = 0;
                pthread_mutex_unlock(&philo->table->alive_mutex);
                break;
            }
            pthread_mutex_unlock(&philo->table->alive_mutex);

            print_status(philo, "is sleeping");
            usleep(philo->table->t_sleep * 1000);  // Tempo de dormir

            // Verificação de morte após dormir
            pthread_mutex_lock(&philo->table->alive_mutex);
            if (get_time() - philo->last_meal > philo->table->t_die)
            {
                print_status(philo, "died");
                philo->table->is_alive = 0;
                pthread_mutex_unlock(&philo->table->alive_mutex);
                break;
            }
            pthread_mutex_unlock(&philo->table->alive_mutex);

            print_status(philo, "is thinking");
            usleep(1000);
        }
    // }
	return (NULL);
}

int init(t_philosopher *philo, t_table *table)
{
    int i;

    i = 0;
    if (!init_forks(table))
        return (0);
    while (i < table->n_philo)
    {
        philo[i].id = i + 1;
        philo[i].eaten = 0;
        philo[i].left_fork = i;
        philo[i].rigth_fork = (i + 1) % table->n_philo;
        philo[i].table = table;
        i++;
    }
    i = 0;
    while (i < table->n_philo)
    {
        pthread_create(&philo[i].thread, NULL, simulation, &philo[i]);
        i++;
    }
    i = 0;
    pthread_create(&philo->death_thread, NULL, verify_death, &philo[i]);
    while (i < table->n_philo)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
    pthread_join(philo->death_thread, NULL);
    return (1);
}
