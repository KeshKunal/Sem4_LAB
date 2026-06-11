/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Implement FCFS disk scheduling.

Logic:
1. Read request sequence and head position.
2. Service requests in given order.
3. Sum total head movement.

Key Variables:
- req[] -> disk requests
- head -> current head position
- total -> total head movement

Algorithm Used:
- First-Come-First-Serve (FCFS) disk scheduling

==================================================
*/

/*
Program Name: FCFS Disk Scheduling
Aim: Write a C program to implement First-Come-First-Serve (FCFS) disk scheduling algorithm.
Algorithm:
1. Read disk requests and head position.
2. Service in given order.
3. Calculate total head movement.
Compilation: gcc 9b_fcfs_disk_scheduling.c -o fcfsdisk
Execution: ./fcfsdisk
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_REQ 50

int main(void)
{
    int n, head;
    int req[MAX_REQ];

    // Input Section
    printf("Enter number of requests (1-%d): ", MAX_REQ);
    scanf("%d", &n);

    printf("Enter request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    // Processing Section
    int total = 0;
    int current = head;
    for (int i = 0; i < n; i++) {
        total += abs(req[i] - current);
        current = req[i];
    }

    // Output Section
    printf("Total Head Movement (FCFS): %d\n", total);

    return 0;
}
