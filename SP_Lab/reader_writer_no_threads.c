#include <stdio.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

int main() {
    int shared_data = 0;
    int readcount = 0;
    int writer_waiting = 0;

    printf("Reader-Writer Problem (Simulation Without Threads)\n");
    printf("===================================================\n\n");

    // Simulate multiple readers and writers (sequential execution)
    for (int round = 1; round <= 3; round++) {
        printf("--- Round %d ---\n", round);

        // Simulate all readers in this round
        for (int r = 1; r <= NUM_READERS; r++) {
            // Entry section: increase readcount
            readcount++;
            printf("Reader %d enters. Readcount = %d\n", r, readcount);

            // Critical section: read
            printf("Reader %d is reading. Shared data = %d\n", r, shared_data);

            // Exit section: decrease readcount
            readcount--;
            printf("Reader %d exits. Readcount = %d\n", r, readcount);
        }

        // Simulate writers
        for (int w = 1; w <= NUM_WRITERS; w++) {
            // Entry section: acquire exclusive access
            printf("Writer %d acquires exclusive access.\n", w);

            // Critical section: write
            shared_data++;
            printf("Writer %d is writing. Shared data updated to %d\n", w, shared_data);

            // Exit section: release exclusive access
            printf("Writer %d releases exclusive access.\n", w);
        }

        printf("\n");
    }

    printf("Final shared data value: %d\n", shared_data);
    return 0;
}
