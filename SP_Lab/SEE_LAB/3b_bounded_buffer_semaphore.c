/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Demonstrate bounded-buffer using semaphores.
- Producer and consumer work on a circular buffer.

Logic:
1. Use semaphores: empty, full, mutex.
2. Producer inserts items into buffer.
3. Consumer removes items from buffer.

Key Variables:
- buffer[] -> circular buffer
- in/out -> indices

Algorithm Used:
- Producer-Consumer with semaphores

==================================================
*/

/*
Program Name: Bounded Buffer using Semaphore
Aim: Write a C program to illustrate Bounded-Buffer problem using a Semaphore.
Algorithm:
1. Initialize semaphores and buffer.
2. Producer adds items and signals full.
3. Consumer removes items and signals empty.
Compilation: gcc 3b_bounded_buffer_semaphore.c -o buffer -pthread
Execution: ./buffer
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
