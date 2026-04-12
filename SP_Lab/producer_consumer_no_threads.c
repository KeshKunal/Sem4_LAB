#include <stdio.h>

#define SIZE 5
#define TOTAL_ITEMS 5

int main() {
    int buffer[SIZE];
    int in = 0, out = 0;
    int count = 0; // Number of items currently in buffer.

    printf("Producer-Consumer (Simulation Without Threads)\n");
    printf("----------------------------------------------\n");

    // Simulate producer and consumer actions alternately.
    for (int item = 1; item <= TOTAL_ITEMS; item++) {
        // Producer step.
        if (count < SIZE) {
            buffer[in] = item;
            printf("Produced: %d at index %d\n", item, in);
            in = (in + 1) % SIZE;
            count++;
        } else {
            printf("Buffer full. Producer waits.\n");
        }

        // Consumer step.
        if (count > 0) {
            int consumed = buffer[out];
            printf("Consumed: %d from index %d\n", consumed, out);
            out = (out + 1) % SIZE;
            count--;
        } else {
            printf("Buffer empty. Consumer waits.\n");
        }
    }

    return 0;
}
