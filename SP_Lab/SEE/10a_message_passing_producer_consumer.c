#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define TOTAL_ITEMS 10

typedef struct {
    sem_t empty;
    sem_t full;
} Sync;

struct msgbuf {
    long mtype;
    int item;
};

int main(void) {
    int msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    if (msgid < 0) {
        perror("msgget failed");
        return 1;
    }

    int shmid = shmget(IPC_PRIVATE, sizeof(Sync), IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget failed");
        return 1;
    }

    Sync *sync = (Sync *)shmat(shmid, NULL, 0);
    if (sync == (void *)-1) {
        perror("shmat failed");
        return 1;
    }

    sem_init(&sync->empty, 1, BUFFER_SIZE);
    sem_init(&sync->full, 1, 0);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        for (int i = 1; i <= TOTAL_ITEMS; i++) {
            sem_wait(&sync->full);

            struct msgbuf msg;
            if (msgrcv(msgid, &msg, sizeof(msg.item), 1, 0) < 0) {
                perror("msgrcv failed");
                exit(1);
            }
            printf("Consumer received: %d\n", msg.item);

            sem_post(&sync->empty);
            usleep(150000);
        }

        shmdt(sync);
        exit(0);
    } else {
        for (int item = 1; item <= TOTAL_ITEMS; item++) {
            sem_wait(&sync->empty);

            struct msgbuf msg;
            msg.mtype = 1;
            msg.item = item;
            if (msgsnd(msgid, &msg, sizeof(msg.item), 0) < 0) {
                perror("msgsnd failed");
                return 1;
            }
            printf("Producer sent: %d\n", item);

            sem_post(&sync->full);
            usleep(100000);
        }

        wait(NULL);
        sem_destroy(&sync->empty);
        sem_destroy(&sync->full);
        shmdt(sync);
        shmctl(shmid, IPC_RMID, NULL);
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}
