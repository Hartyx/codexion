// Les étapes
// Verrouiller log_mutex.
// Lire le flag stop (protégé par state_mutex, donc on le verrouille brièvement pour lire).
// Si stop vaut 0, calculer get_time_ms() - start_time et afficher temps id message.
// Déverrouiller dans l'ordre inverse.


#include "codexion.h"

void	log_state(t_coder *coder, char *msg)
{
	t_data	*data;
	int		stopped;

	data = coder->data;
	pthread_mutex_lock(&data->log_mutex);
	pthread_mutex_lock(&data->state_mutex);
	stopped = data->stop;
	pthread_mutex_unlock(&data->state_mutex);
	if (!stopped)
		printf("%ld %d %s\n", get_time_ms() - data->start_time,
			coder->id, msg);
	pthread_mutex_unlock(&data->log_mutex);
}
