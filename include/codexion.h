/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safidyan <safidyan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 07:56:02 by safidyan          #+#    #+#             */
/*   Updated: 2026/10/11 01:02:07 by safidyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
#define CODEXION_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <limits.h>


typedef struct  s_config
{
    int nb_coders;
    long    time_to_burnout;
    long    time_to_compile;
    long    time_to_debug;
    long    time_to_refactor;
    int nb_compiles_required;
    long    dongle_cooldown;
    int use_edf;
}   t_config;

typedef struct s_data t_data;

typedef struct s_dongle
{
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    int taken;
    long    available_at;
}   t_dongle;

typedef struct s_coder
{
    int id;
    pthread_t   thread;
    t_dongle    *left;
    t_dongle    *right;
    long    last_compile_start;
    int nb_compiles;
    t_data  *data;
}   t_coder;


struct s_data
{
    t_config    cfg;
    long    start_time;
    int stop;
    t_coder *coders;
    t_dongle    *dongles;
    pthread_mutex_t log_mutex;
    pthread_mutex_t state_mutex;
};

int		parse_args(int argc, char **argv, t_config *cfg);
long	get_time_ms(void);
void	sleep_ms(long ms);
void	cleanup(t_data *data);
int	init_data(t_data *data, t_config *cfg);
void    log_state(t_coder *coder, char *msg);
void    *coder_routine(void *arg);
int start_simulation(t_data *data);
void	destroy_dongles(t_data *data, int count);
void	take_dongle(t_coder *coder, t_dongle *dongle);
void	release_dongle(t_dongle *dongle, long cooldown);
#endif