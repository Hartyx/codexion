
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h> // Pour la fonction usleep

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	sleep_ms(long ms)
{
	long	end;

	end = get_time_ms() + ms;
	while (get_time_ms() < end)
		usleep(200);
}



int main() {
    struct timeval debut, fin;

    // 1. Obtenir le temps avant l'opération
    gettimeofday(&debut, NULL);
    printf("Temps de début : %ld secondes et %ld microsecondes\n", debut.tv_sec, debut.tv_usec);

    // Simulation d'une tâche qui dure 500 millisecondes (500 000 microsecondes)
    usleep(500000);

    // 2. Obtenir le temps après l'opération
    gettimeofday(&fin, NULL);
    printf("Temps de fin   : %ld secondes et %ld microsecondes\n", fin.tv_sec, fin.tv_usec);

    // 3. Calculer la différence en microsecondes
    long secondes = fin.tv_sec - debut.tv_sec;
    long microsecondes = fin.tv_usec - debut.tv_usec;
    long temps_total_usec = (secondes * 1000000) + microsecondes;

    printf("Durée totale de l'exécution : %ld microsecondes (soit %.3f secondes)\n", 
            temps_total_usec, (double)temps_total_usec / 1000000.0);

    return 0;
}
