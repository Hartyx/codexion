/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safidyan <safidyan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 12:19:49 by safidyan          #+#    #+#             */
/*   Updated: 2026/10/17 14:13:09 by safidyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "codexion.h"

static int  check_burnout(t_data *data)
{
    int i;
    long now;
    int burned;

    i = 0;
    burned = 0;
    now = get_time_ms();
    pthread_mutex_lock(&data->state_mutex);
    while(i  < data->cfg.nb_coders && !burned)
    {   
        if((data->coders[i].nb_compiles < data->cfg.nb_compiles_required)
        && (now - data->coders[i].last_compile_start >= data->cfg.time_to_burnout))
            burned = data->coders[i].id;
        i++;
    }
    pthread_mutex_unlock(&data->state_mutex);
    return (burned);
    
}

static int  all_done(t_data *data)
{
    int i;
    int done;

    i = 0;
    done = 1;
    pthread_mutex_lock(&data->state_mutex);
    while(i < data->cfg.nb_coders)
    {
        if(data->coders[i].nb_compiles < data->cfg.nb_compiles_required)
            done = 0;
        i++;
    }
    pthread_mutex_unlock(&data->state_mutex);
    return (done);
}

void    *monitor_routine(void *arg)
{
    t_data *data;
    int burned;

    data = (t_data *)arg;
    while (!is_stopped(data))
    {
        burned = check_burnout(data);
        if (burned != 0)
        {
            log_burnout(&data->coders[burned - 1]);
            return (NULL);
        }
        else if (all_done(data))
        {
            set_stop(data);
            return (NULL);
        }
        usleep(1000);
    }
    return (NULL);
}
