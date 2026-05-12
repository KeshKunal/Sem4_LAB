#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define NUM 5
#define ROUNDS 3

sem_t forks[NUM];
sem_t room;

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % NUM;

    for (int i = 0; i < ROUNDS; i++) {
        printf("Philosopher %d is thinking.\n", id);
        usleep(150000);

        sem_wait(&room);
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);

        printf("Philosopher %d is eating.\n", id);
        usleep(200000);

        sem_post(&forks[right]);
        sem_post(&forks[left]);
        sem_post(&room);
    }

    return NULL;
}

int main(void) {
    pthread_t threads[NUM];
    int ids[NUM];

    for (int i = 0; i < NUM; i++) {
        sem_init(&forks[i], 0, 1);
    }
    sem_init(&room, 0, NUM - 1);

    for (int i = 0; i < NUM; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < NUM; i++) {
        sem_destroy(&forks[i]);
    }
    sem_destroy(&room);

    return 0;
}
