/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Demonstrate fork() creating separate parent/child copies.
- Show global and local variables in both processes.

Logic:
1. Initialize global and local variables.
2. fork() creates child.
3. Child modifies variables; parent prints original values.

Key Variables:
- globalVar -> global variable
- localVar -> local variable

Algorithm Used:
- fork() process creation

==================================================
*/

/*
Program Name: fork() Variables Demo
Aim: Write a C program to demonstrate how fork() creates separate parent and child processes with independent copies of global and local variables.
Algorithm:
1. Initialize variables.
2. fork() and modify in child.
3. Print in child and parent.
Compilation: gcc 4a_fork_variables.c -o forkdemo
Execution: ./forkdemo
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int globalVar = 100;

int main(void)
{
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
