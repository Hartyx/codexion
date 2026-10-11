#include "codexion.h"

static void	take_forks(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	if (coder->left < coder->right)
	{
		first = coder->left;
		second = coder->right;
	}
	else
	{
		first = coder->right;
		second = coder->left;
	}
	take_dongle(coder, first);
	take_dongle(coder, second);
}

static void	start_compile(t_coder *coder)
{
	t_data	*data;

	data = coder->data;
	pthread_mutex_lock(&data->state_mutex);
	coder->last_compile_start = get_time_ms();
	coder->nb_compiles++;
	pthread_mutex_unlock(&data->state_mutex);
	log_state(coder, "is compiling");
}

static void	release_forks(t_coder *coder)
{
	long	cooldown;

	cooldown = coder->data->cfg.dongle_cooldown;
	release_dongle(coder->left, cooldown);
	release_dongle(coder->right, cooldown);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	t_data	*data;

	coder = (t_coder *)arg;
	data = coder->data;
	while (coder->nb_compiles < data->cfg.nb_compiles_required)
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
	return (NULL);
}
