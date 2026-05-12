#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("Child before execvp. PID = %d\n", getpid());
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent: child finished execution.\n");
    }

    return 0;
}
