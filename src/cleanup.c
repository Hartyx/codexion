/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: safidyan <safidyan@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 07:56:09 by safidyan          #+#    #+#             */
/*   Updated: 2026/10/10 07:10:21 by safidyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_dongles(t_data *data, int count)
{
	int	i = 0;

	i = 0;
	while(i < count)
	{
		pthread_mutex_destroy(&data->dongles[i].mutex);
		pthread_cond_destroy(&data->dongles[i].cond);
		i++;
	}
}

void	cleanup(t_data *data)
{
	if(data->dongles)
	{
		destroy_dongles(data, data->cfg.nb_coders);
		free(data->dongles);
	}
	free(data->coders);
	pthread_mutex_destroy(&data->log_mutex);
	pthread_mutex_destroy(&data->state_mutex);
}
