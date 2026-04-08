#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define TOTAL_ITEMS 10

int main(void) {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child is consumer: read items from pipe
        close(fd[1]);

        for (int i = 1; i <= TOTAL_ITEMS; i++) {
            int item;
            if (read(fd[0], &item, sizeof(item)) > 0) {
                printf("Consumer received: %d\n", item);
            }
        }

        close(fd[0]);
        exit(0);
    } else {
        // Parent is producer: write items to pipe
        close(fd[0]);

        for (int item = 1; item <= TOTAL_ITEMS; item++) {
            write(fd[1], &item, sizeof(item));
            printf("Producer sent: %d\n", item);
            usleep(120000);
        }

        close(fd[1]);
        wait(NULL);
    }

    return 0;
}
