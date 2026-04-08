#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

int sharedData = 0;
int readCount = 0;

sem_t rwMutex;      // Controls access for writers (and first/last reader)
pthread_mutex_t rcMutex; // Protects readCount updates

void *reader(void *arg) {
    int id = *(int *)arg;

    pthread_mutex_lock(&rcMutex);
    readCount++;
    if (readCount == 1) {
        // First reader blocks writers
        sem_wait(&rwMutex);
    }
    pthread_mutex_unlock(&rcMutex);

    printf("Reader %d reads sharedData = %d\n", id, sharedData);
    usleep(150000);

    pthread_mutex_lock(&rcMutex);
    readCount--;
    if (readCount == 0) {
        // Last reader allows writers
        sem_post(&rwMutex);
    }
    pthread_mutex_unlock(&rcMutex);

    return NULL;
}

void *writer(void *arg) {
    int id = *(int *)arg;

    sem_wait(&rwMutex);
    sharedData += 10;
    printf("Writer %d writes sharedData = %d\n", id, sharedData);
    usleep(200000);
    sem_post(&rwMutex);

    return NULL;
}

int main(void) {
    pthread_t r[3], w[2];
    int rid[3] = {1, 2, 3};
    int wid[2] = {1, 2};

    sem_init(&rwMutex, 0, 1);
    pthread_mutex_init(&rcMutex, NULL);

    pthread_create(&w[0], NULL, writer, &wid[0]);
    pthread_create(&r[0], NULL, reader, &rid[0]);
    pthread_create(&r[1], NULL, reader, &rid[1]);
    pthread_create(&w[1], NULL, writer, &wid[1]);
    pthread_create(&r[2], NULL, reader, &rid[2]);

    for (int i = 0; i < 3; i++) {
        pthread_join(r[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(w[i], NULL);
    }

    sem_destroy(&rwMutex);
    pthread_mutex_destroy(&rcMutex);

    return 0;
}
