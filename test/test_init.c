#include "test_codexion.h"

static int	init_dongles(t_data *data)
{
	int	i;

	data->dongles = malloc(sizeof(t_dongle) * data->cfg.nb_coders);
	if (!data->dongles)
		return (1);
	i = 0;
	while (i < data->cfg.nb_coders)
	{
		pthread_mutex_init(&data->dongles[i].mutex, NULL);
		data->dongles[i].taken = 0;
		data->dongles[i].available_at = 0;
		i++;
	}
	return (0);
}

static int	init_coders(t_data *data)
{
	int	i;
	int	n;

	n = data->cfg.nb_coders;
	data->coders = malloc(sizeof(t_coder) * n);
	if (!data->coders)
		return (1);
	i = 0;
	while (i < n)
	{
		data->coders[i].id = i + 1;
		data->coders[i].left = &data->dongles[(i + n - 1) % n];
		data->coders[i].right = &data->dongles[i];
		data->coders[i].last_compile_start = data->start_time;
		data->coders[i].nb_compiles = 0;
		data->coders[i].data = data;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, t_config *cfg)
{
	data->cfg = *cfg;
	data->stop = 0;
	data->coders = NULL;
	data->dongles = NULL;
	data->start_time = get_time_ms();
	if (init_dongles(data))
		return (1);
	if (init_coders(data))
		return (cleanup(data), 1);
	pthread_mutex_init(&data->log_mutex, NULL);
	pthread_mutex_init(&data->state_mutex, NULL);
	return (0);
}

static int	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->log_mutex, NULL))
		return (1);
	if (pthread_mutex_init(&data->state_mutex, NULL))
	{
		pthread_mutex_destroy(&data->log_mutex);
		return (1);
	}
	return (0);
}
int	init_data(t_data *data, t_config *cfg)
{
	memset(data, 0, sizeof(t_data));
	data->cfg = *cfg;
	data->start_time = get_time_ms();
	if (init_mutexes(data))
		return (1);
	if (init_dongles(data))
	{
		cleanup(data);
		return (1);
	}
	if (init_coders(data))
	{
		cleanup(data);
		return (1);
	}
	return (0);
}
/*
static int	init_one_dongle(t_dongle *dongle)
{
	if (pthread_mutex_init(&dongle->mutex, NULL))
		return (1);
	if (pthread_cond_init(&dongle->cond, NULL))
	{
		pthread_mutex_destroy(&dongle->mutex);
		return (1);
	}
	dongle->taken = 0;
	dongle->available_at = 0;
	return (0);
}

static int	init_dongles(t_data *data)
{
	int	i;

	data->dongles = malloc(sizeof(t_dongle) * data->cfg.nb_coders);
	if (!data->dongles)
		return (1);
	i = 0;
	while (i < data->cfg.nb_coders)
	{
		if (init_one_dongle(&data->dongles[i]))
		{
			destroy_dongles(data, i);
			free(data->dongles);
			data->dongles = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

remplace
static int	init_one_dongle(t_dongle *dongle)
{
	dongle->taken = 0;
	dongle->available_at = 0;
	dongle->ticket = 0;
	if (pthread_mutex_init(&dongle->mutex, NULL))
		return (1);
	if (pthread_cond_init(&dongle->cond, NULL))
	{
		pthread_mutex_destroy(&dongle->mutex);
		return (1);
	}
	if (heap_init(&dongle->queue, 2))
	{
		pthread_cond_destroy(&dongle->cond);
		pthread_mutex_destroy(&dongle->mutex);
		return (1);
	}
	return (0);
}
*/

