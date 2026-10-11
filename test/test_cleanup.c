#include "codexion.h"


/*
Sous-étape 1 : préparer les dongles à l’attente

Un codeur qui trouve un dongle pris doit dormir jusqu’à ce qu’il soit libre, sans tourner dans le vide. Il faut donc :

ajouter un champ pthread_cond_t dans t_dongle ;
l’initialiser dans init_dongles avec pthread_cond_init ;
le détruire dans cleanup avec pthread_cond_destroy.

Profites-en pour régler le point resté en suspens : init_dongles doit tester le retour de pthread_mutex_init. En cas d’échec au dongle i, elle détruit ce qui existe déjà (dongles 0 à i - 1), libère le tableau et remet data->dongles à NULL.
*/

void	destroy_dongles(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&data->dongles[i].mutex);
		pthread_cond_destroy(&data->dongles[i].cond);
		i++;
	}
}

void	cleanup(t_data *data)
{
	if (data->dongles)
	{
		destroy_dongles(data, data->cfg.nb_coders);
		free(data->dongles);
	}
	free(data->coders);
	pthread_mutex_destroy(&data->log_mutex);
	pthread_mutex_destroy(&data->state_mutex);
}