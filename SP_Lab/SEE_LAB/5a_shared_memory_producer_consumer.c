/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Demonstrate IPC using shared memory.
- Producer writes a value; consumer reads it.

Logic:
1. Create shared memory segment.
2. Fork into producer and consumer.
3. Use a flag for simple synchronization.

Algorithm Used:
- Producer-Consumer using shared memory

shmget() → create shared memory
shmat() → attach shared memory
shmdt() → detach
shmctl() → delete
==================================================
*/

/*
Program Name: Producer Consumer using Shared Memory
Aim: Write a C program to demonstrate IPC using shared memory by implementing the Producer-Consumer problem.
Algorithm:
1. Create and attach shared memory.
2. Fork into producer and consumer.
3. Producer writes fixed items, consumer reads them.
4. Cleanup shared memory.
Compilation: gcc 5a_shared_memory_producer_consumer.c -o pc_shm
Execution: ./pc_shm
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

struct shared {
    int data; // shared item
    int flag; // 0 = empty, 1 = full
};

int main(void)
{
    int shmid;
    struct shared *shm;

    shmid = shmget(IPC_PRIVATE, sizeof(struct shared), IPC_CREAT | 0666);
    shm = (struct shared *)shmat(shmid, NULL, 0);
    shm->flag = 0;

    if (fork() == 0) {
        // Consumer
        for (int i = 1; i <= 5; i++) {
            while (shm->flag == 0);
            printf("Consumed: %d\n", shm->data);
            shm->flag = 0;
            sleep(1);
        }
    } else {
        // Producer
        for (int i = 1; i <= 5; i++) {
            while (shm->flag == 1);
            shm->data = i;
            printf("Produced: %d\n", i);
            shm->flag = 1;
            sleep(1);
        }

        wait(NULL);
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}

/*
Sample Output:
Produced: 1
Consumed: 1
... (continues up to 5)
*/
