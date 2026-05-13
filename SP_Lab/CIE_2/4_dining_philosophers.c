/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Demonstrate Dining Philosophers with deadlock avoidance.
- Each philosopher needs two forks to eat.
- Use a room semaphore to prevent deadlock.

Logic:
1. Read number of philosophers (n).
2. Create semaphore for each fork and one extra "room" = n-1.
3. Each philosopher thread picks room, then two forks, eats, releases.

Key Variables:
- forks[] -> semaphore for each fork
- room -> semaphore limiting entry
- n -> number of philosophers (<= MAX)

Algorithm Used:
- Dining Philosophers with room (deadlock avoidance, threads)

==================================================
*/

/*
Program Name: Dining Philosophers Synchronization
Aim: Write a C program to demonstrate synchronization and deadlock handling using the Dining Philosophers problem.
Algorithm:
1. Read number of philosophers.
2. Initialize semaphores for forks and room.
3. Create philosopher threads.
4. Each philosopher thinks, eats, and releases forks.
Compilation: gcc 4_dining_philosophers.c -o dining -pthread
Execution: ./dining
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

    // Enter room
    sem_wait(&room);

    // Pick left and right forks
    sem_wait(&forks[left]);
    sem_wait(&forks[right]);

    printf("Philosopher %d is eating.\n", id + 1);

    sleep(1);

    // Put forks back
    sem_post(&forks[right]);
    sem_post(&forks[left]);

    // Leave room
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
