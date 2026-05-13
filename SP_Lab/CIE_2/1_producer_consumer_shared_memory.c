/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Show IPC using shared memory.
- Producer writes items into a shared buffer.
- Consumer reads items from the buffer.
- Use simple busy waiting on count to avoid conflict.

Logic:
1. Create and attach shared memory for buffer and control variables.
2. Fork: parent = producer, child = consumer.
3. Producer writes, consumer reads, update in/out and count.

Key Variables:
- buffer[] -> shared circular buffer
- in, out -> write/read positions
- count -> number of items in buffer

Algorithm Used:
- Producer-Consumer using shared memory + busy wait

==================================================
*/

/*
Program Name: Producer Consumer using Shared Memory (Simple)
Aim: Write a program to demonstrate Inter-Process Communication (IPC) using shared memory by implementing the Producer Consumer problem.
Algorithm:
1. Create and initialize shared memory.
2. Fork producer and consumer.
3. Producer writes fixed items, consumer reads fixed items.
4. Cleanup shared memory.
Compilation: gcc 1_producer_consumer_shared_memory.c -o pc_shm
Execution: ./pc_shm
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define SIZE 5

// Shared memory structure
struct shared
{
    int buffer[SIZE];
    int in;
    int out;
    int count;
};

int main()
{
    int shmid;
    struct shared *shm;

    // Input Section
    // No user input; fixed 5 items are produced and consumed.

    // Processing Section
    // Create shared memory
    shmid = shmget(IPC_PRIVATE, sizeof(struct shared), IPC_CREAT | 0666);

    // Attach shared memory
    shm = (struct shared *)shmat(shmid, NULL, 0);

    // Initialize
    shm->in = 0;
    shm->out = 0;
    shm->count = 0;

    // Create child process
    if(fork() == 0)
    {
        // Consumer
        for(int i = 1; i <= 5; i++)
        {
            // Wait if buffer empty
            while(shm->count == 0);

            // Consume item
            // Output Section
            printf("Consumed: %d\n", shm->buffer[shm->out]);

            shm->out = (shm->out + 1) % SIZE;
            shm->count--;

            sleep(1);
        }
    }
    else
    {
        // Producer
        for(int i = 1; i <= 5; i++)
        {
            // Wait if buffer full
            while(shm->count == SIZE);

            // Produce item
            shm->buffer[shm->in] = i;
            // Output Section
            printf("Produced: %d\n", i);

            shm->in = (shm->in + 1) % SIZE;
            shm->count++;

            sleep(1);
        }

        wait(NULL);

        // Remove shared memory
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }

    /* Time Complexity: O(n) for n items (here n = 5). */
    return 0;
}

/*
Sample Input:
No input

Sample Output:
Produced: 1
Consumed: 1
Produced: 2
Consumed: 2
Produced: 3
Consumed: 3
Produced: 4
Consumed: 4
Produced: 5
Consumed: 5
*/
