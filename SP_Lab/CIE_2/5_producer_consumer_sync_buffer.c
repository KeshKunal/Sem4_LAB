/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Synchronize producer and consumer threads with a shared buffer.
- Use semaphores for empty, full, and mutex.
- Show correct produce/consume ordering.

Logic:
1. Initialize semaphores: mutex, empty, full.
2. Create producer and consumer threads.
3. Producer writes fixed items, consumer reads fixed items.

Key Variables:
- buffer -> shared single-slot buffer
- empty, full, mutex -> semaphores

Algorithm Used:
- Producer-Consumer using semaphores (threads)

==================================================
*/

/*
Program Name: Producer Consumer with Synchronization (Shared Buffer)
Aim: Write a c program to demonstrate synchronization between producer-consumer threads that share a common buffer and perform a read and write operation to and from the buffer.
Algorithm:
1. Initialize semaphores.
2. Producer waits on empty and mutex, writes item.
3. Consumer waits on full and mutex, reads item.
4. Join threads and finish.
Compilation: gcc 5_producer_consumer_sync_buffer.c -o pc_sync -pthread
Execution: ./pc_sync
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int buffer;

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

    return NULL;
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

    return NULL;
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

/*
Sample Input:
No input

Sample Output:
Produced: 1
Consumed: 1
Produced: 2
Consumed: 2
Produced: 3
Consumed: 3
Produced: 4
Consumed: 4
Produced: 5
Consumed: 5
*/
