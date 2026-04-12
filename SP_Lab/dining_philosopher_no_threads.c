#include <stdio.h>

#define NUM 5
#define CYCLES 3

int main() {
    // fork_state[i] = 0 means free, 1 means in use.
    int fork_state[NUM] = {0};

    printf("Dining Philosophers (Simulation Without Threads)\n");
    printf("------------------------------------------------\n");

    for (int round = 1; round <= CYCLES; round++) {
        printf("\nRound %d\n", round);

        // Simulate each philosopher one by one.
        for (int id = 0; id < NUM; id++) {
            int left = id;
            int right = (id + 1) % NUM;

            printf("Philosopher %d is thinking.\n", id);

            // In simulation, philosopher eats only if both forks are free.
            if (fork_state[left] == 0 && fork_state[right] == 0) {
                fork_state[left] = 1;
                fork_state[right] = 1;

                printf("Philosopher %d picked forks %d and %d.\n", id, left, right);
                printf("Philosopher %d is eating.\n", id);

                // Put forks back after eating.
                fork_state[left] = 0;
                fork_state[right] = 0;
                printf("Philosopher %d released forks and finished eating.\n", id);
            } else {
                printf("Philosopher %d could not eat (fork not available).\n", id);
            }
        }
    }

    return 0;
}
