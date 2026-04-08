#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define ITEMS_TO_PRODUCE 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t emptySlots, fullSlots;
pthread_mutex_t mutex;

void *producer(void *arg) {
    for (int item = 1; item <= ITEMS_TO_PRODUCE; item++) {
        sem_wait(&emptySlots);          // Wait for empty slot
        pthread_mutex_lock(&mutex);     // Enter critical section

        buffer[in] = item;
        printf("Produced: %d at index %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);   // Leave critical section
        sem_post(&fullSlots);           // Signal that an item is available

        usleep(150000);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 1; i <= ITEMS_TO_PRODUCE; i++) {
        sem_wait(&fullSlots);           // Wait for available item
        pthread_mutex_lock(&mutex);     // Enter critical section

        int item = buffer[out];
        printf("Consumed: %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);   // Leave critical section
        sem_post(&emptySlots);          // Signal that one slot is free

        usleep(220000);
    }
    return NULL;
}

int main(void) {
    pthread_t prodThread, consThread;

    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&fullSlots, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
    pthread_mutex_destroy(&mutex);

    return 0;
}
