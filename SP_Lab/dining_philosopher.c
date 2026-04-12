#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM 5
pthread_mutex_t forks[NUM];

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % NUM;

    while (1) {
        // Step 1: Think
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        // Step 2: Pick forks
        // Deadlock avoidance: last philosopher picks right fork first.
        if (id == NUM - 1) {
            pthread_mutex_lock(&forks[right]);
            pthread_mutex_lock(&forks[left]);
        } else {
            pthread_mutex_lock(&forks[left]);
            pthread_mutex_lock(&forks[right]);
        }

        // Step 3: Eat
        printf("Philosopher %d is EATING.\n", id);
        sleep(2);

        // Step 4: Put forks back
        pthread_mutex_unlock(&forks[left]);
        pthread_mutex_unlock(&forks[right]);
        printf("Philosopher %d finished eating.\n", id);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM];
    int ids[NUM];

    for (int i = 0; i < NUM; i++) {
        pthread_mutex_init(&forks[i], NULL);
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM; i++) pthread_join(threads[i], NULL);
    return 0;
}