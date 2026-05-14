/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Show IPC using shared memory.
- Producer writes items into a single shared variable.
- Consumer reads items from that variable.
- Use simple busy waiting on a flag to avoid conflict.

Logic:
1. Create and attach shared memory for data and a flag.
2. Fork: parent = producer, child = consumer.
3. Producer writes, consumer reads, update flag.

Key Variables:
- data -> single shared item
- flag -> 0 = empty, 1 = full

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
#include <sys/shm.h> // shared memory
#include <sys/wait.h>
#include <unistd.h>

// Shared memory structure
struct shared
{
    int data; // single shared item
    int flag; // 0 = empty, 1 = full
};

int main()
{
    int shmid; // stores shared memory id
    struct shared *shm; // stores pointer to shared block

    // Input Section
    // No user input; fixed 5 items are produced and consumed.

    // Processing Section
    // Create shared memory
    shmid = shmget(IPC_PRIVATE, sizeof(struct shared), IPC_CREAT | 0666);

    // Attach shared memory
    shm = (struct shared *)shmat(shmid, NULL, 0);

    // Initialize
    shm->flag = 0;

    // Create child process
    if(fork() == 0)
    {
        // Consumer
        for(int i = 1; i <= 5; i++)
        {
            // Wait if no item available --> this is busy waiting
            while(shm->flag == 0);

            // Consume item
            // Output Section
            printf("Consumed: %d\n", shm->data);
            shm->flag = 0;

            sleep(1);
        }
    }
    else
    {
        // Producer
        for(int i = 1; i <= 5; i++)
        {
            // Wait if item not yet consumed --> until this is true it waits
            while(shm->flag == 1);

            // Produce item
            shm->data = i;
            // Output Section
            printf("Produced: %d\n", i);
            shm->flag = 1;

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
