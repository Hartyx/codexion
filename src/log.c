/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safidyan <safidyan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/06 23:46:26 by safidyan          #+#    #+#             */
/*   Updated: 2026/10/08 22:18:06 by safidyan         ###   ########.fr       */
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
