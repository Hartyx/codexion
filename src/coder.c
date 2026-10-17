/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safidyan <safidyan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 22:15:24 by safidyan          #+#    #+#             */
/*   Updated: 2026/10/17 15:28:18 by safidyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


static int  wait_stop(t_coder   *coder, t_dongle *dongle)
{
    while(!is_stopped(coder->data))
        usleep(500);
    release_dongle(dongle, 0);
    return (1);
}
static int take_forks(t_coder  *coder)
{
    t_dongle    *first;
    t_dongle    *second;

    first = coder->left;
    second = coder->right;
    if(coder->left > coder->right)
    {
        first = coder->right;
        second = coder->left;
    }
    if (take_dongle(coder, first))
        return (1);
    if(first == second)
        return (wait_stop(coder, first));
    if (take_dongle(coder, second))
    {
        release_dongle(first, 0);
        return (1);
    }
    return (0);
}

static void start_compile(t_coder *coder)
{
    t_data  *data;

    data = coder->data;
    pthread_mutex_lock(&data->state_mutex);
    coder->last_compile_start = get_time_ms();
    coder->nb_compiles++;
    pthread_mutex_unlock(&data->state_mutex);
    log_state(coder, "is compiling");
}

static void release_forks(t_coder   *coder)
{   
    long    cooldown;
    
    cooldown = coder->data->cfg.dongle_cooldown;
    release_dongle(coder->left, cooldown);
    release_dongle(coder->right, cooldown);
    pthread_mutex_lock(&coder->data->state_mutex);
    coder->nb_compiles++;
    pthread_mutex_unlock(&coder->data->state_mutex);
}

void    *coder_routine(void *arg)
{
    t_coder *coder;
    t_data  *data;

    coder = (t_coder *)arg;
    data = coder->data;
    while(coder->nb_compiles < data->cfg.nb_compiles_required && !is_stopped(data))
    {
        take_forks(coder);
        start_compile(coder);
        sleep_ms(data->cfg.time_to_compile);
        release_forks(coder);
        log_state(coder, "is debugging");
        sleep_ms(data->cfg.time_to_debug);
        log_state(coder, "is refactoring");
        sleep_ms(data->cfg.time_to_refactor);
    }
    return NULL;
}
