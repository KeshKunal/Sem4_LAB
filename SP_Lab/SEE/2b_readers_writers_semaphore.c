#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t wrt;
sem_t mutex;
int readcount = 0;
int shared_data = 0;

void *reader(void *arg) {
    int id = *(int *)arg;

    sem_wait(&mutex);
    readcount++;
    if (readcount == 1) {
        sem_wait(&wrt);
    }
    sem_post(&mutex);

    printf("Reader %d reads shared_data = %d\n", id, shared_data);
    usleep(150000);

    sem_wait(&mutex);
    readcount--;
    if (readcount == 0) {
        sem_post(&wrt);
    }
    sem_post(&mutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&wrt);
    shared_data += 10;
    printf("Writer %d writes shared_data = %d\n", id, shared_data);
    usleep(200000);
    sem_post(&wrt);

    return NULL;
}

int main(void) {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS] = {1, 2, 3};
    int writer_ids[NUM_WRITERS] = {1, 2};

    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&wrt);
    sem_destroy(&mutex);

    return 0;
}
