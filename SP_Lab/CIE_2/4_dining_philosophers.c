/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Demonstrate Dining Philosophers with deadlock avoidance.
- Each philosopher needs two forks to eat.
- Use a room semaphore to prevent deadlock.

Logic:
1. Create semaphore for each fork.
2. Create one extra semaphore "room" = n-1.
3. Philosopher picks room, then two forks, eats, releases.

Key Variables:
- forks[] -> semaphore for each fork
- room -> semaphore limiting entry

Algorithm Used:
- Dining Philosophers with room (deadlock avoidance)

==================================================
*/

/*
Program Name: Dining Philosophers Synchronization
Aim: Write a C program to demonstrate synchronization and deadlock handling using the Dining Philosophers problem.
Algorithm:
1. Initialize semaphores for forks and room.
2. Fork philosopher processes.
3. Each philosopher thinks, eats, and releases forks.
Compilation: gcc 4_dining_philosophers.c -o dining
Execution: ./dining
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_PHILO 5

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
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
    int n, i, semid;
    union semun su;

    // Input Section
    printf("Enter number of philosophers (2-%d): ", MAX_PHILO);
    if (scanf("%d", &n) != 1 || n < 2 || n > MAX_PHILO) {
        printf("Invalid input.\n");
        return 0;
    }

    // Processing Section
    semid = semget(IPC_PRIVATE, n + 1, IPC_CREAT | 0666);
    if (semid == -1) {
        printf("Semaphore creation failed.\n");
        return 0;
    }

    /* Initialize fork semaphores */
    su.val = 1;
    for (i = 0; i < n; i++) {
        semctl(semid, i, SETVAL, su);
    }

    /* Room semaphore (n-1) */
    su.val = n - 1;
    semctl(semid, n, SETVAL, su);

    for (i = 0; i < n; i++) {
        if (fork() == 0) {
            int left = i;
            int right = (i + 1) % n;

            // Output Section
            printf("Philosopher %d is thinking.\n", i + 1);

            sem_wait_op(semid, n);       /* room */
            sem_wait_op(semid, left);    /* left fork */
            sem_wait_op(semid, right);   /* right fork */

            printf("Philosopher %d is eating.\n", i + 1);
            sleep(1);

            sem_signal_op(semid, right);
            sem_signal_op(semid, left);
            sem_signal_op(semid, n);     /* room */

            printf("Philosopher %d finished eating.\n", i + 1);
            return 0;
        }
    }

    for (i = 0; i < n; i++) {
        wait(NULL);
    }
    semctl(semid, 0, IPC_RMID);

    /* Time Complexity: O(n) for n philosophers (each eats once). */
    return 0;
}

/*
Sample Input:
Enter number of philosophers (2-5): 5

Sample Output:
Philosopher 1 is thinking.
Philosopher 1 is eating.
Philosopher 1 finished eating.
... (similar for others)
*/
