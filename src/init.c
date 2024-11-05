/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:02:56 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/05 11:33:50 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

void *verify_death(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;
    t_table *table = philo->table;
    long time;
    int i;

    while (1)
    {
        i = 0;
        while (i < table->n_philo)
        {
            pthread_mutex_lock(&table->alive_mutex);
            time = get_time();
            if (time - philo[i].last_meal > table->t_die + 4)
            {
                print_status(&philo[i], "died");
                table->is_alive = 0;
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
            break;
        }
        pthread_mutex_unlock(&table->alive_mutex);
    }
    return (NULL);
}

int philosopher_routine(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->table->alive_mutex);
    if (!philo->table->is_alive)
    {
        pthread_mutex_unlock(&philo->table->alive_mutex);
        return (0);
    }
    pthread_mutex_unlock(&philo->table->alive_mutex);

    print_status(philo, "is eating");
    pthread_mutex_lock(&philo->table->alive_mutex);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->table->alive_mutex);

    usleep(philo->table->t_cat * 1000);
    drop_forks(philo);

    print_status(philo, "is sleeping");
    usleep(philo->table->t_sleep * 1000);
    print_status(philo, "is thinking");

    return (1);
}

void *simulation(void *arg)
{
    t_philosopher *philo = (t_philosopher *)arg;

    if (philo->table->n_philo == 1)
    {
        pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
        print_status(philo, "has taken a fork");
        while (1)
        {
            if (philo->table->is_alive != 1)
                break;
        }
        pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
        return (NULL);
    }

    while (1)
    {
        get_forks(philo);
        pthread_mutex_lock(&philo->table->alive_mutex);
        if (!philo->table->is_alive)
        {
            pthread_mutex_unlock(&philo->table->alive_mutex);
            drop_forks(philo);
            break;
        }
        pthread_mutex_unlock(&philo->table->alive_mutex);

        if (!philosopher_routine(philo))
            break;
    }
    return (NULL);
}

int init(t_philosopher *philo, t_table *table)
{
    int i;

    if (!init_forks(table))
        return (0);

    // Inicializa os filósofos e suas threads
    for (i = 0; i < table->n_philo; i++)
    {
        philo[i].id = i + 1;
        philo[i].eaten = 0;
        philo[i].left_fork = i;
        philo[i].rigth_fork = (i + 1) % table->n_philo;
        philo[i].table = table;
        philo[i].last_meal = get_time();
    }

    // Criação da thread de monitoramento de morte
    pthread_create(&philo->death_thread, NULL, verify_death, philo);

    // Criação das threads dos filósofos
    for (i = 0; i < table->n_philo; i++)
        pthread_create(&philo[i].thread, NULL, simulation, &philo[i]);

    // Espera as threads dos filósofos terminarem
    for (i = 0; i < table->n_philo; i++)
        pthread_join(philo[i].thread, NULL);

    // Espera a thread de verificação de morte terminar
    pthread_join(philo->death_thread, NULL);

    return (1);
}
