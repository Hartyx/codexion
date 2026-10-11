#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

int compteur = 0;
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;

void *ma_fonction(void *arg)
{   
    int i = 0;
    while (i < 10)
    {   
        pthread_mutex_lock(&verrou);
        compteur++;
        printf("i = %d, compteur = %d\n", i, compteur);
        pthread_mutex_unlock(&verrou);
        i++;
    }
    return NULL;
}

int main(void)
{   
    pthread_t t1, t2;

    pthread_create(&t1, NULL, ma_fonction, NULL);
    pthread_create(&t2, NULL, ma_fonction, NULL);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("compteur = %d\n", compteur);
    return 0;
}