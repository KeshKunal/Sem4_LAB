#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define TOTAL_ITEMS 10

typedef struct {
    sem_t mutex;
    sem_t empty;
    sem_t full;
    int buffer[BUFFER_SIZE];
    int in;
    int out;
} SharedData;

int main(void) {
    int shmid = shmget(IPC_PRIVATE, sizeof(SharedData), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget failed");
        return 1;
    }

    SharedData *data = (SharedData *)shmat(shmid, NULL, 0);
    if (data == (void *)-1) {
        perror("shmat failed");
        return 1;
    }

    data->in = 0;
    data->out = 0;

    // pshared = 1 allows semaphore sharing between related processes
    sem_init(&data->mutex, 1, 1);
    sem_init(&data->empty, 1, BUFFER_SIZE);
    sem_init(&data->full, 1, 0);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child acts as consumer
        for (int i = 1; i <= TOTAL_ITEMS; i++) {
            sem_wait(&data->full);
            sem_wait(&data->mutex);

            int item = data->buffer[data->out];
            printf("Consumer consumed: %d\n", item);
            data->out = (data->out + 1) % BUFFER_SIZE;

            sem_post(&data->mutex);
            sem_post(&data->empty);

            usleep(180000);
        }

        shmdt(data);
        exit(0);
    } else {
        // Parent acts as producer
        for (int item = 1; item <= TOTAL_ITEMS; item++) {
            sem_wait(&data->empty);
            sem_wait(&data->mutex);

            data->buffer[data->in] = item;
            printf("Producer produced: %d\n", item);
            data->in = (data->in + 1) % BUFFER_SIZE;

            sem_post(&data->mutex);
            sem_post(&data->full);

            usleep(100000);
        }

        wait(NULL);

        sem_destroy(&data->mutex);
        sem_destroy(&data->empty);
        sem_destroy(&data->full);
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
