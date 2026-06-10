/*
==================================================
QUICK OVERVIEW
==================================================

Purpose:
 - Demonstrate the Dining Philosophers problem and a simple deadlock-avoidance
     strategy using a "room" semaphore.

Approach:
 1. Read number of philosophers (n), up to MAX.
 2. Create one binary semaphore per fork and a "room" semaphore initialized to n-1.
        Limiting concurrent philosophers to n-1 prevents circular wait and thus deadlock.
 3. Each philosopher thread: think -> enter room -> pick two forks -> eat -> release forks -> leave room.

Key variables:
 - `forks[]`: semaphore for each fork (binary semaphore, value 1 means available).
 - `room`: semaphore limiting how many philosophers may try to pick forks simultaneously.
 - `n`: number of philosophers actually used (must be <= MAX).

Notes:
 - This program demonstrates a simple, practical deadlock avoidance technique.
 - The code does not currently destroy semaphores; consider adding `sem_destroy` calls
     if the program is extended.
 - Compile with `gcc 1b_dining_philosophers_semaphore.c -o dining -pthread` on POSIX systems
     (Windows may require different build flags/toolchain).

==================================================
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX 10

sem_t forks[MAX];
sem_t room;

int n; // number of philosophers

// Philosopher function
void *philosopher(void *num)
{
    int id = *(int *)num;

    int left = id;
    int right = (id + 1) % n;

    printf("Philosopher %d is thinking.\n", id + 1);

    // Enter room (limits concurrent philosophers to avoid deadlock)
    sem_wait(&room);

    // Pick left and right forks (binary semaphores ensure mutual exclusion)
    sem_wait(&forks[left]);
    sem_wait(&forks[right]);

    printf("Philosopher %d is eating.\n", id + 1);

    sleep(1);

    // Put forks back (release in any order) and leave the room
    sem_post(&forks[right]);
    sem_post(&forks[left]);

    // Leave room (allow another philosopher to try picking forks)
    sem_post(&room);

    printf("Philosopher %d finished eating.\n", id + 1);

    return NULL;
}

int main()
{
    pthread_t p[MAX];
    int id[MAX];

    // User input
    printf("Enter number of philosophers: ");
    scanf("%d", &n);

    // Initialize room semaphore
    sem_init(&room, 0, n - 1);

    // Initialize forks
    for(int i = 0; i < n; i++)
    {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for(int i = 0; i < n; i++)
    {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    // Wait for all philosophers
    for(int i = 0; i < n; i++)
    {
        pthread_join(p[i], NULL);
    }

    /* Time Complexity: O(n) for n philosophers (each eats once). */
    return 0;
}

/*
Sample Input:
Enter number of philosophers: 5

Sample Output:
Philosopher 1 is thinking.
Philosopher 1 is eating.
Philosopher 1 finished eating.
... (similar for others)
*/
