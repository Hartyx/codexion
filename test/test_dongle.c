#include "codexion.h"

static void	wait_dongle(t_dongle *dongle)
{
	struct timespec	ts;

	while (dongle->taken || get_time_ms() < dongle->available_at)
	{
		if (dongle->taken)
			pthread_cond_wait(&dongle->cond, &dongle->mutex);
		else
		{
			ts.tv_sec = dongle->available_at / 1000;
			ts.tv_nsec = (dongle->available_at % 1000) * 1000000;
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

/*
#include "codexion.h"

static void	wait_dongle(t_data *data, t_dongle *dongle)
{
	struct timespec	ts;

	while ((dongle->taken || get_time_ms() < dongle->available_at)
		&& !is_stopped(data))
	{
		if (dongle->taken)
			pthread_cond_wait(&dongle->cond, &dongle->mutex);
		else
		{
			ts.tv_sec = dongle->available_at / 1000;
			ts.tv_nsec = (dongle->available_at % 1000) * 1000000;
			pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &ts);
		}
	}
}

int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	wait_dongle(coder->data, dongle);
	if (is_stopped(coder->data))
	{
		pthread_mutex_unlock(&dongle->mutex);
		return (1);
	}
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
	pthread_cond_signal(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}
*/