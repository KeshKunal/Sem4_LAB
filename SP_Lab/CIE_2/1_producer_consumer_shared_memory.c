/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Show IPC using shared memory.
- Producer writes items into a shared buffer.
- Consumer reads items from the buffer.
- Use a simple turn flag to avoid conflict (busy wait).

Logic:
1. Create shared memory for buffer and control variables.
2. Fork: parent = producer, child = consumer.
3. Producer writes, consumer reads, update in/out and count.

Key Variables:
- buffer[] -> shared circular buffer
- in, out -> write/read positions
- count -> number of items in buffer
- turn -> 0 producer, 1 consumer

Algorithm Used:
- Producer-Consumer using shared memory + turn flag

==================================================
*/

/*
Program Name: Producer Consumer using Shared Memory (Simple)
Aim: Write a program to demonstrate Inter-Process Communication (IPC) using shared memory by implementing the Producer Consumer problem.
Algorithm:
1. Get number of items.
2. Create and initialize shared memory.
3. Producer writes items, consumer reads items using turn flag.
4. Cleanup shared memory.
Compilation: gcc 1_producer_consumer_shared_memory.c -o pc_shm
Execution: ./pc_shm
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 20

struct shared_data {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    int count;
    int turn; /* 0 = producer, 1 = consumer */
};

int main(void)
{
    int shmid;
    struct shared_data *data;
    int n, i;

    // Input Section
    printf("Enter number of items to produce (1-%d): ", MAX_ITEMS);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_ITEMS) {
        printf("Invalid input.\n");
        return 0;
    }

    // Processing Section
    shmid = shmget(IPC_PRIVATE, sizeof(struct shared_data), IPC_CREAT | 0666);
    if (shmid == -1) {
        printf("Shared memory creation failed.\n");
        return 0;
    }

    data = (struct shared_data *)shmat(shmid, NULL, 0);
    if (data == (void *)-1) {
        printf("Shared memory attach failed.\n");
        return 0;
    }

    data->in = 0;
    data->out = 0;
    data->count = 0;
    data->turn = 0;

    if (fork() == 0) {
        /* Consumer process */
        for (i = 1; i <= n; i++) {
            while (data->count == 0 || data->turn == 0) {
                /* Busy wait */
            }
            // Output Section
            printf("Consumer consumed: %d\n", data->buffer[data->out]);
            data->out = (data->out + 1) % BUFFER_SIZE;
            data->count--;
            data->turn = 0;
        }
        shmdt(data);
        return 0;
    } else {
        /* Producer process */
        for (i = 1; i <= n; i++) {
            while (data->count == BUFFER_SIZE || data->turn == 1) {
                /* Busy wait */
            }
            data->buffer[data->in] = i;
            // Output Section
            printf("Producer produced: %d\n", i);
            data->in = (data->in + 1) % BUFFER_SIZE;
            data->count++;
            data->turn = 1;
        }
        wait(NULL);
        shmdt(data);
        shmctl(shmid, IPC_RMID, NULL);
    }

    /* Time Complexity: O(n) for n items. */
    return 0;
}

/*
Sample Input:
Enter number of items to produce (1-20): 3

Sample Output:
Producer produced: 1
Consumer consumed: 1
Producer produced: 2
Consumer consumed: 2
Producer produced: 3
Consumer consumed: 3
*/
