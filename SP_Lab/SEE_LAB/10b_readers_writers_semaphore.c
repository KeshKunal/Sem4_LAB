/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Illustrate Readers-Writers synchronization using semaphores.

Logic:
1. Use mutex to protect readcount.
2. First reader locks writer semaphore, last reader releases.
3. Writers get exclusive access.

Key Variables:
- readcount -> number of active readers
- wrt, mutex -> semaphores

Algorithm Used:
- Readers-Writers with semaphores

==================================================
*/

/*
Program Name: Readers-Writers using Semaphores
Aim: Write a program to illustrate the Readers-Writers problem using semaphores.
Algorithm:
1. Initialize semaphores.
2. Create reader and writer threads.
3. Readers can read concurrently; writers are exclusive.
Compilation: gcc 10b_readers_writers_semaphore.c -o rw -pthread
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
    printf("Reader %d reads data = %d\n", id, data);
    sleep(1);
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

    sem_wait(&wrt);
    data = data + 10;
    printf("Writer %d writes data = %d\n", id, data);
    sleep(1);
    sem_post(&wrt);

    return NULL;
}

int main()
{
    int r, w;

    printf("Enter number of readers: ");
    scanf("%d", &r);

    printf("Enter number of writers: ");
    scanf("%d", &w);

    pthread_t readers[r], writers[w];

    int rid[r], wid[w];

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

    for(int i = 0; i < r; i++)
    {
        pthread_join(readers[i], NULL);
    }

    for(int i = 0; i < w; i++)
    {
        pthread_join(writers[i], NULL);
    }

    return 0;
}
