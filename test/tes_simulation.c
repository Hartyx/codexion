#include "codexion.h"

static void	set_start_times(t_data *data)
{
	int	i;

	data->start_time = get_time_ms();
	i = 0;
	while (i < data->cfg.nb_coders)
	{
		data->coders[i].last_compile_start = data->start_time;
		i++;
	}
}

static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cfg.nb_coders)
	{
		if (pthread_create(&data->coders[i].thread, NULL,
				coder_routine, &data->coders[i]))
			return (i);
		i++;
	}
	return (i);
}

static void	join_threads(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_join(data->coders[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_data *data)
{
	int	created;

	set_start_times(data);
	created = create_threads(data);
	join_threads(data, created);
	if (created != data->cfg.nb_coders)
		return (1);
	return (0);
}