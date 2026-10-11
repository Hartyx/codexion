/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safidyan <safidyan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 07:56:18 by safidyan          #+#    #+#             */
/*   Updated: 2026/10/09 23:39:26 by safidyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long    get_time_ms(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
void    sleep_ms(long ms)
{
    long    end;

    end = get_time_ms() + ms;
    while (get_time_ms() < end)
        usleep(200);
}