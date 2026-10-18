// #include "codexion.h"

static long	get_key(t_coder *coder, t_dongle *dongle)
{
	long	key;

	if (!coder->data->cfg.use_edf)
	{
		key = dongle->ticket;
		dongle->ticket++;
		return (key);
	}
	pthread_mutex_lock(&coder->data->state_mutex);
	key = coder->last_compile_start + coder->data->cfg.time_to_burnout;
	pthread_mutex_unlock(&coder->data->state_mutex);
	return (key);
}

static int	must_wait(t_coder *coder, t_dongle *dongle)
{
	if (is_stopped(coder->data))
		return (0);
	if (dongle->taken || get_time_ms() < dongle->available_at)
		return (1);
	return (heap_top_id(&dongle->queue) != coder->id);
}

static void	wait_dongle(t_coder *coder, t_dongle *dongle)
{
	struct timespec	ts;

	while (must_wait(coder, dongle))
	{
		if (!dongle->taken && get_time_ms() < dongle->available_at)
		{
			ts.tv_sec = dongle->available_at / 1000;
			ts.tv_nsec = (dongle->available_at % 1000) * 1000000;
			pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &ts);
		}
		else
			pthread_cond_wait(&dongle->cond, &dongle->mutex);
	}
}

int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	long	key;

	pthread_mutex_lock(&dongle->mutex);
	key = get_key(coder, dongle);
	if (heap_push(&dongle->queue, key, coder->id))
	{
		pthread_mutex_unlock(&dongle->mutex);
		return (1);
	}
	wait_dongle(coder, dongle);
	if (is_stopped(coder->data))
	{
		pthread_mutex_unlock(&dongle->mutex);
		return (1);
	}
	heap_pop(&dongle->queue);
	dongle->taken = 1;
	pthread_mutex_unlock(&dongle->mutex);
	log_state(coder, "has taken a dongle");
	return (0);
}

void	release_dongle(t_dongle *dongle, long cooldown)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->taken = 0;
	dongle->available_at = get_time_ms() + cooldown;
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}