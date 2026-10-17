/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safidyan <safidyan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 23:46:26 by safidyan          #+#    #+#             */
/*   Updated: 2026/10/17 10:37:45 by safidyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

void    log_state(t_coder *coder, char *msg)
{
    t_data *data;
    int stopped;

    data = coder -> data;
    pthread_mutex_lock(&data->log_mutex);
    pthread_mutex_lock(&data->state_mutex);
    stopped = data -> stop;
    pthread_mutex_unlock(&data -> state_mutex);
    if (!stopped)
        printf("%ld %d %s\n", get_time_ms() - data -> start_time, coder->id, msg);
    pthread_mutex_unlock(&data -> log_mutex);
}

void    log_burnout(t_coder *coder)
{
    t_data  *data;
    
    data = coder->data;
    pthread_mutex_lock(&data->log_mutex);
    if (!is_stopped(data))
        printf("%ld %d burned out\n",
            get_time_ms() - data->start_time, coder->id);
    set_stop(data);
    pthread_mutex_unlock(&data->log_mutex);
}