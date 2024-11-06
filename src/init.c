/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:02:56 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/06 09:12:54 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"


int philosopher_routine(t_philosopher *philo)
{
    int meals_needed = philo->table->n_times_eat;
    int meals_count = 0;
        
    while (1)
    {
        get_forks(philo);

        // Verifica se o filósofo ainda está vivo
        pthread_mutex_lock(&philo->table->alive_mutex);
        if (!philo->table->is_alive)  // Verifica o sinal global
        {
            pthread_mutex_unlock(&philo->table->alive_mutex);
            drop_forks(philo);
            return 0;
        }
        pthread_mutex_unlock(&philo->table->alive_mutex);

        print_status(philo, "is eating");
        
        // Atualiza o tempo da última refeição
        pthread_mutex_lock(&philo->table->alive_mutex);
        philo->last_meal = get_time();
        pthread_mutex_unlock(&philo->table->alive_mutex);

        usleep(philo->table->t_cat * 1000);
        meals_count += 1;

        drop_forks(philo);
        print_status(philo, "is sleeping");
        usleep(philo->table->t_sleep * 1000);
        print_status(philo, "is thinking");

        if (meals_needed != -1 && meals_count >= meals_needed)
        {
            pthread_mutex_lock(&philo->table->alive_mutex);
            philo->table->finished_eating_count++;
            if (philo->table->finished_eating_count == philo->table->n_philo)
            {
                philo->table->is_alive = 0;  // Interrompe o programa
                printf("All philosophers have eaten enough\n");
            }
            pthread_mutex_unlock(&philo->table->alive_mutex);
            return 0;  // Sai do loop ao completar refeições
        }
    }
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
    for (i = 0; i < table->n_philo; i++)
    {
        philo[i].id = i + 1;
        philo[i].eaten = 0;
        philo[i].left_fork = i;
        philo[i].rigth_fork = (i + 1) % table->n_philo;
        philo[i].table = table;
        philo[i].last_meal = get_time();
    }
    for (i = 0; i < table->n_philo; i++)
        pthread_create(&philo[i].thread, NULL, simulation, &philo[i]);
    pthread_create(&philo->death_thread, NULL, verify_death, philo);
    for (i = 0; i < table->n_philo; i++)
        pthread_join(philo[i].thread, NULL);
    pthread_join(philo->death_thread, NULL);
    return (1);
}
