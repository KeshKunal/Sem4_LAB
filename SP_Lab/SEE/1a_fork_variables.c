#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int globalVar = 100;

int main(void) {
    int localVar = 200;
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        globalVar += 50;
        localVar += 50;
        printf("Child Process\n");
        printf("  PID: %d\n", getpid());
        printf("  globalVar = %d\n", globalVar);
        printf("  localVar  = %d\n", localVar);
        exit(0);
    } else {
        wait(NULL);
        printf("Parent Process\n");
        printf("  PID: %d\n", getpid());
        printf("  globalVar = %d\n", globalVar);
        printf("  localVar  = %d\n", localVar);
    }

    return 0;
}
