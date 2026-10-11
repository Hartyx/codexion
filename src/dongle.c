/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safidyan <safidyan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 00:26:12 by safidyan          #+#    #+#             */
/*   Updated: 2026/10/11 09:10:40 by safidyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void wait_dongle(t_dongle *dongle)
{
    struct  timespec    ts;

    while(dongle->taken || get_time_ms() < dongle->available_at)
    {
        if (dongle->taken)
            pthread_cond_wait(&dongle->cond, &dongle->mutex);
        else
        {
            ts.tv_sec = dongle->available_at / 1000;
            ts.tv_nsec = (dongle->available_at % 1000) * 100000;
            pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &ts);
        }
    }
}

void	take_dongle(t_coder *coder, t_dongle *dongle)
{
    pthread_mutex_lock(&dongle->mutex);
    wait_dongle(dongle);
    dongle->taken = 1;
    pthread_mutex_unlock(&dongle->mutex);
    log_state(coder, "has taken a dongle");
}

void	release_dongle(t_dongle *dongle, long cooldown)
{
    pthread_mutex_lock(&dongle->mutex);
    dongle->taken = 0;
    dongle->available_at = get_time_ms() + cooldown;
    pthread_cond_signal(&dongle->cond);
    pthread_mutex_unlock(&dongle->mutex);
}
