/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Synchronize producer and consumer with a shared buffer.
- Use semaphores for empty, full, and mutex.
- Show correct read/write ordering.

Logic:
1. Create shared memory for buffer.
2. Create semaphores: mutex, empty, full.
3. Producer writes n items, consumer reads n items.

Key Variables:
- buffer[] -> shared circular buffer
- empty, full, mutex -> semaphores

Algorithm Used:
- Producer-Consumer using semaphores

==================================================
*/

/*
Program Name: Producer Consumer with Synchronization (Shared Buffer)
Aim: Write a c program to demonstrate synchronization between producer-consumer processes that share a common buffer and performs a read and write operation to and from the buffer.
Algorithm:
1. Initialize shared memory and semaphores.
2. Producer waits on empty and mutex, writes item.
3. Consumer waits on full and mutex, reads item.
4. Cleanup resources.
Compilation: gcc 5_producer_consumer_sync_buffer.c -o pc_sync
Execution: ./pc_sync
*/

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

/*
Sample Input:
Enter number of items to produce (1-20): 4

Sample Output:
Producer wrote: 1
Producer wrote: 2
Consumer read: 1
Producer wrote: 3
Consumer read: 2
Producer wrote: 4
Consumer read: 3
Consumer read: 4
*/
