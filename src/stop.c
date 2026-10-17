/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safidyan <safidyan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 08:08:53 by safidyan          #+#    #+#             */
/*   Updated: 2026/10/16 13:42:36 by safidyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

int is_stopped(t_data *data)
{
    int stopped;

    pthread_mutex_lock(&data->state_mutex);
    stopped = data->stop;
    pthread_mutex_unlock(&data->state_mutex);
    return (stopped);
}

void wake_all_dongles(t_data *data)
{
    int i;

    i = 0;
    while(i < data->cfg.nb_coders)
    {
        pthread_mutex_lock(&data->dongles[i].mutex);
        pthread_cond_broadcast(&data->dongles[i].cond);
        pthread_mutex_unlock(&data->dongles[i].mutex);
        i++;
    }
}

void    set_stop(t_data *data)
{
    pthread_mutex_lock(&data->state_mutex);
    data->stop = 1;
    pthread_mutex_unlock(&data->state_mutex);
    wake_all_dongles(data);
}