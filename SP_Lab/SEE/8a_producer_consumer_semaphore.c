#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define ITEMS_TO_PRODUCE 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t emptySlots;
sem_t fullSlots;
sem_t mutex;

void *producer(void *arg) {
    for (int item = 1; item <= ITEMS_TO_PRODUCE; item++) {
        sem_wait(&emptySlots);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("Produced: %d at index %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&fullSlots);
        usleep(150000);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 1; i <= ITEMS_TO_PRODUCE; i++) {
        sem_wait(&fullSlots);
        sem_wait(&mutex);

        int item = buffer[out];
        printf("Consumed: %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&emptySlots);
        usleep(220000);
    }
    return NULL;
}

int main(void) {
    pthread_t prodThread, consThread;

    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&fullSlots, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
    sem_destroy(&mutex);

    return 0;
}
