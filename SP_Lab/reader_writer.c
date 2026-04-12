#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

// Semaphore to control writer access to shared resource
sem_t wrt;

// Semaphore to protect readcount variable (critical section)
sem_t mutex;

// Number of readers currently reading
int readcount = 0;

// Shared resource (data)
int shared_data = 0;

// Reader thread function
void *reader(void *arg) {
    int id = *(int *)arg;

    // ===== Entry Section =====
    // Wait for mutex to protect readcount
    sem_wait(&mutex);
    readcount++;

    // If this is the first reader, block the writer (acquire wrt)
    if (readcount == 1) {
        sem_wait(&wrt);
    }
    sem_post(&mutex);

    // ===== Critical Section: Read =====
    printf("Reader %d is reading. Shared data: %d\n", id, shared_data);
    sleep(1);

    // ===== Exit Section =====
    // Wait for mutex to protect readcount
    sem_wait(&mutex);
    readcount--;

    // If this is the last reader, release writer (give wrt back)
    if (readcount == 0) {
        sem_post(&wrt);
    }
    sem_post(&mutex);

    return NULL;
}

// Writer thread function
void *writer(void *arg) {
    int id = *(int *)arg;

    // ===== Entry Section =====
    // Wait for exclusive access to shared resource
    sem_wait(&wrt);

    // ===== Critical Section: Write =====
    printf("Writer %d is writing.\n", id);
    shared_data++;
    sleep(2);

    // ===== Exit Section =====
    // Release exclusive access
    sem_post(&wrt);

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize semaphores
    // wrt = 1 (writer not blocked initially)
    // mutex = 1 (one thread at a time can access readcount)
    sem_init(&wrt, 0, 1);
    sem_init(&mutex, 0, 1);

    printf("Reader-Writer Problem (Readers have priority)\n");
    printf("=============================================\n\n");

    // Create reader threads
    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for all reader threads to complete
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Wait for all writer threads to complete
    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&wrt);
    sem_destroy(&mutex);

    printf("\nAll readers and writers finished.\n");
    return 0;
}
