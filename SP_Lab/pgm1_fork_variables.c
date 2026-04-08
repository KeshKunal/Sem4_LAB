#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Global variable (copied separately into parent and child after fork)
int globalVar = 100;

int main(void) {
    int localVar = 200; // Local variable (also copied during fork)

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // Child process modifies its own copy
        globalVar += 50;
        localVar += 50;

        printf("Child Process\n");
        printf("  PID: %d\n", getpid());
        printf("  globalVar = %d\n", globalVar);
        printf("  localVar  = %d\n", localVar);
        exit(0);
    } else {
        // Parent waits so output is easy to read
        wait(NULL);

        // Parent values remain unchanged
        printf("Parent Process\n");
        printf("  PID: %d\n", getpid());
        printf("  globalVar = %d\n", globalVar);
        printf("  localVar  = %d\n", localVar);
    }

    return 0;
}
