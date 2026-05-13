/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Demonstrate Readers-Writers synchronization.
- Multiple readers can read together.
- Writer gets exclusive access.

Logic:
1. Use shared variables for data and readcount.
2. Use semaphores: mutex for readcount, wrt for writer.
3. Readers follow entry/exit protocol.
4. Writers lock wrt, update data, unlock.

Key Variables:
- read_count -> number of active readers
- data -> shared data item
- mutex, wrt -> semaphores

Algorithm Used:
- Readers-Writers (readers preference)

==================================================
*/

/*
Program Name: Readers Writers Synchronization
Aim: Write a program to demonstrate synchronization in shared resource access using the Readers-Writers problem.
Algorithm:
1. Initialize semaphores.
2. Create reader and writer threads.
3. Apply readers-writers entry/exit rules.
4. Join threads and finish.
Compilation: gcc 3_readers_writers.c -o rw -pthread
Execution: ./rw
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int data = 0;
int readcount = 0;

sem_t mutex, wrt;

// Reader function
void *reader(void *arg)
{
    int id = *(int *)arg;

    // Update readcount
    sem_wait(&mutex);

    readcount++;

    // First reader blocks writer
    if(readcount == 1)
    {
        sem_wait(&wrt);
    }

    sem_post(&mutex);

    // Reading section
    printf("Reader %d reads data = %d\n", id, data);

    sleep(1);

    // Exit section
    sem_wait(&mutex);

    readcount--;

    // Last reader allows writer
    if(readcount == 0)
    {
        sem_post(&wrt);
    }

    sem_post(&mutex);

    return NULL;
}

// Writer function
void *writer(void *arg)
{
    int id = *(int *)arg;

    // Writer enters
    sem_wait(&wrt);

    data = data + 10;

    printf("Writer %d writes data = %d\n", id, data);

    sleep(1);

    // Writer exits
    sem_post(&wrt);

    return NULL;
}

int main()
{
    int r, w;

    // Input Section
    printf("Enter number of readers: ");
    scanf("%d", &r);

    printf("Enter number of writers: ");
    scanf("%d", &w);

    pthread_t readers[r], writers[w];

    int rid[r], wid[w];

    // Processing Section
    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for(int i = 0; i < r; i++)
    {
        rid[i] = i + 1;

        pthread_create(&readers[i], NULL, reader, &rid[i]);
    }

    // Create writer threads
    for(int i = 0; i < w; i++)
    {
        wid[i] = i + 1;

        pthread_create(&writers[i], NULL, writer, &wid[i]);
    }

    // Wait for readers
    for(int i = 0; i < r; i++)
    {
        pthread_join(readers[i], NULL);
    }

    // Wait for writers
    for(int i = 0; i < w; i++)
    {
        pthread_join(writers[i], NULL);
    }

    /* Time Complexity: O(r + w). */
    return 0;
}

/*
Sample Input:
Enter number of readers: 2
Enter number of writers: 1

Sample Output:
Writer 1 writes data = 10
Reader 1 reads data = 10
Reader 2 reads data = 10
*/
