#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int a, b;
    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        char aStr[20], bStr[20];
        snprintf(aStr, sizeof(aStr), "%d", a);
        snprintf(bStr, sizeof(bStr), "%d", b);

        execl("./11b_exec_add_child", "11b_exec_add_child", aStr, bStr, (char *)NULL);
        perror("execl failed");
        exit(1);
    } else {
        wait(NULL);
        printf("Parent: child finished.\n");
    }

    return 0;
}
