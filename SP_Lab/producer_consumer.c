#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5
int buffer[SIZE], in = 0, out = 0;
sem_t empty, full, mutex;

void *producer(void *arg) {
    for (int i = 0; i < 5; i++) {
        int item = i + 1;
        // Wait for a free slot, then enter critical section.
        sem_wait(&empty);
        sem_wait(&mutex);
        
        // Insert item into circular buffer.
        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % SIZE;
        
        // Exit critical section and signal availability of one item.
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *arg) {
    for (int i = 0; i < 5; i++) {
        // Wait for available item, then enter critical section.
        sem_wait(&full);
        sem_wait(&mutex);
        
        // Remove item from circular buffer.
        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % SIZE;
        
        // Exit critical section and signal one free slot.
        sem_post(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t p, c;
    // empty = SIZE initially (all slots free), full = 0, mutex = 1.
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    return 0;
}