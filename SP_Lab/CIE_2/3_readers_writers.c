/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Demonstrate Readers-Writers synchronization.
- Multiple readers can read together.
- Writer gets exclusive access.

Logic:
1. Use shared memory for data and read_count.
2. Use semaphores: mutex for read_count, wrt for writer.
3. Readers follow entry/exit protocol.
4. Writers lock wrt, update data, unlock.

Key Variables:
- read_count -> number of active readers
- data -> shared data item
- mutex, wrt -> semaphores

Algorithm Used:
- Readers-Writers (readers preference)

==================================================
*/

/*
Program Name: Readers Writers Synchronization
Aim: Write a program to demonstrate synchronization in shared resource access using the Readers-Writers problem.
Algorithm:
1. Initialize shared memory and semaphores.
2. Fork reader and writer processes.
3. Apply readers-writers entry/exit rules.
4. Cleanup shared memory and semaphores.
Compilation: gcc 3_readers_writers.c -o rw
Execution: ./rw
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_RW 5

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

struct shared_data {
    int read_count;
    int data;
};

static void sem_wait_op(int semid, int semnum)
{
    struct sembuf op;
    op.sem_num = semnum;
    op.sem_op = -1;
    op.sem_flg = 0;
    semop(semid, &op, 1);
}

static void sem_signal_op(int semid, int semnum)
{
    struct sembuf op;
    op.sem_num = semnum;
    op.sem_op = 1;
    op.sem_flg = 0;
    semop(semid, &op, 1);
}

int main(void)
{
    int shmid, semid;
    struct shared_data *data;
    int readers, writers, i;
    union semun su;

    // Input Section
    printf("Enter number of readers (1-%d): ", MAX_RW);
    if (scanf("%d", &readers) != 1 || readers < 1 || readers > MAX_RW) {
        printf("Invalid input.\n");
        return 0;
    }
    printf("Enter number of writers (1-%d): ", MAX_RW);
    if (scanf("%d", &writers) != 1 || writers < 1 || writers > MAX_RW) {
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
    data->read_count = 0;
    data->data = 0;

    semid = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    if (semid == -1) {
        printf("Semaphore creation failed.\n");
        return 0;
    }
    su.val = 1;
    semctl(semid, 0, SETVAL, su); /* mutex */
    semctl(semid, 1, SETVAL, su); /* wrt */

    /* Create reader processes */
    for (i = 0; i < readers; i++) {
        if (fork() == 0) {
            // Entry Section
            sem_wait_op(semid, 0);
            data->read_count++;
            if (data->read_count == 1) {
                sem_wait_op(semid, 1);
            }
            sem_signal_op(semid, 0);

            // Output Section
            printf("Reader %d reads data = %d\n", i + 1, data->data);
            sleep(1);

            // Exit Section
            sem_wait_op(semid, 0);
            data->read_count--;
            if (data->read_count == 0) {
                sem_signal_op(semid, 1);
            }
            sem_signal_op(semid, 0);

            shmdt(data);
            return 0;
        }
    }

    /* Create writer processes */
    for (i = 0; i < writers; i++) {
        if (fork() == 0) {
            sem_wait_op(semid, 1);
            data->data = data->data + 10;
            // Output Section
            printf("Writer %d writes data = %d\n", i + 1, data->data);
            sleep(1);
            sem_signal_op(semid, 1);

            shmdt(data);
            return 0;
        }
    }

    // Wait for all children
    for (i = 0; i < readers + writers; i++) {
        wait(NULL);
    }

    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);

    /* Time Complexity: O(r + w) for r readers and w writers. */
    return 0;
}

/*
Sample Input:
Enter number of readers (1-5): 2
Enter number of writers (1-5): 1

Sample Output:
Writer 1 writes data = 10
Reader 1 reads data = 10
Reader 2 reads data = 10
*/
