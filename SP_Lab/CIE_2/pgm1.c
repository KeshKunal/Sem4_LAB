#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int buffer;   // shared variable

sem_t empty, full, mutex;

// Producer
void *producer()
{
    for(int i = 1; i <= 5; i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer = i;
        printf("Produced: %d\n", buffer);

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }
}

// Consumer
void *consumer()
{
    for(int i = 1; i <= 5; i++)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        printf("Consumed: %d\n", buffer);

        sem_post(&mutex);
        sem_post(&empty);

        sleep(1);
    }
}

int main()
{
    pthread_t p1, p2;

    // Initialize semaphores
    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create threads
    pthread_create(&p1, NULL, producer, NULL);
    pthread_create(&p2, NULL, consumer, NULL);

    // Wait for threads
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    return 0;
}