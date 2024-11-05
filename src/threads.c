/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emalungo <emalungo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 16:23:53 by emalungo          #+#    #+#             */
/*   Updated: 2024/11/05 14:52:26 by emalungo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosopher.h"

static int check_philosopher_death(t_philosopher *philo, t_table *table) 
{
    long time = get_time();
    
    if (time - philo->last_meal > table->t_die)
    {
        print_status(philo, "died");
        table->is_alive = 0;
        return 1;
    }
    return 0;
}

void *verify_death(void *arg) 
{
    t_philosopher *philo = (t_philosopher *)arg;
    t_table *table = philo->table;
    int i;

    while (1)
    {
        i = 0;
        while (i < table->n_philo) {
            pthread_mutex_lock(&table->alive_mutex);
            if (check_philosopher_death(&philo[i], table)) {
                pthread_mutex_unlock(&table->alive_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&table->alive_mutex);
            usleep(100);
            i++;
        }
        pthread_mutex_lock(&table->alive_mutex);
        if (!table->is_alive) {
            pthread_mutex_unlock(&table->alive_mutex);
            break;
        }
        pthread_mutex_unlock(&table->alive_mutex);
    }
    return NULL;
}

