/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safidyan <safidyan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 22:42:03 by safidyan          #+#    #+#             */
/*   Updated: 2026/10/09 05:19:15 by safidyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void set_start_time(t_data *data)
{
    int i;

    data->start_time = get_time_ms();
    i = 0;
    while (i < data->cfg.nb_coders)
    {
        data->coders[i].last_compile_start = data->start_time;
        i++;
    }
}

static int  create_thread(t_data *data)
{
    int i;
    i = 0;
    while(i < data->cfg.nb_coders)
    {   
        if(pthread_create(&data->coders[i].thread, NULL, coder_routine, &data->coders[i]))
            return (i);
        i++;
    }
    return (i);
}


static void join_threads(t_data *data, int count)
{
    int i;
    
    i = 0;
    while(i < count)
    {       
            pthread_join(data->coders[i].thread, NULL);
            i++;
    }
}

int start_simulation(t_data *data)
{
    int created;
    
    set_start_time(data);
    created = create_thread(data);
    join_threads(data, created);
    if (created != data->cfg.nb_coders)
        return (1);
    return (0);
}