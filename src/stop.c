/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safidyan <safidyan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 08:08:53 by safidyan          #+#    #+#             */
/*   Updated: 2026/10/12 08:58:43 by safidyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

int is_stopped(t_data *data)
{
    int stopped;

    pthread_mutex_lock(&data->state_mutex);
    data -> stop = 0;
    
    
}