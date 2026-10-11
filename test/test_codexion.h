/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_codexion.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safidyan <safidyan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 07:56:02 by safidyan          #+#    #+#             */
/*   Updated: 2026/10/05 00:45:04 by safidyan         ###   ########.fr       */
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

typedef struct s_data	t_data;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	int				taken;
	long			available_at;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	t_dongle		*left;
	t_dongle		*right;
	long			last_compile_start;
	int				nb_compiles;
	pthread_t		thread;
	t_data			*data;
}	t_coder;

struct s_data
{
	t_config		cfg;
	long			start_time;
	int				stop;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	state_mutex;
};
int		parse_args(int argc, char **argv, t_config *cfg);
long	get_time_ms(void);
void	sleep_ms(long ms);

#endif