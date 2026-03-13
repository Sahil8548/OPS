#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;
pthread_mutex_t mutex;

int readcount = 0;

void *reader(void *arg)
{
    int id = *(int *)arg;

    pthread_mutex_lock(&mutex);
    readcount++;

    if(readcount == 1)
        sem_wait(&wrt);

    pthread_mutex_unlock(&mutex);

    printf("Reader %d is reading\n", id);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readcount--;

    if(readcount == 0)
        sem_post(&wrt);

    pthread_mutex_unlock(&mutex);

    printf("Reader %d finished reading\n", id);

    return NULL;
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&wrt);

    printf("Writer %d is writing\n", id);
    sleep(1);

    printf("Writer %d finished writing\n", id);

    sem_post(&wrt);

    return NULL;
}

int main()
{
    pthread_t r[5], w[2];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt, 0, 1);

    int i;

    int reader_id[5] = {1,2,3,4,5};
    int writer_id[2] = {1,2};

    for(i = 0; i < 5; i++)
        pthread_create(&r[i], NULL, reader, &reader_id[i]);

    for(i = 0; i < 2; i++)
        pthread_create(&w[i], NULL, writer, &writer_id[i]);

    for(i = 0; i < 5; i++)
        pthread_join(r[i], NULL);

    for(i = 0; i < 2; i++)
        pthread_join(w[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}
