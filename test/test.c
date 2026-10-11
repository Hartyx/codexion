#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


void *telecharger(void *arg)
{   
    int i;
    i = 1;

    while (i <= 5)
    {
        printf("Téléchargement : %d%%\n", i * 20);
        sleep(1);
        i++;
    }
    return NULL;
}

void *lire_video(void *arg)
{
    int i;
    i = 1;
    while (i <= 5)
    {
        printf("Video : seconde %d\n", i);
        sleep(1);
        i++;
    }
    return NULL;
}


int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, telecharger, NULL);
    pthread_create(&t2, NULL, lire_video, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Terminé !\n");
}