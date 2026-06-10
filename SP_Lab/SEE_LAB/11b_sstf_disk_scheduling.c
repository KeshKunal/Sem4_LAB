/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Implement SSTF disk scheduling.

Logic:
1. Read request sequence and head position.
2. Repeatedly pick the closest unserved request.
3. Compute total head movement.

Key Variables:
- req[] -> disk requests
- visited[] -> serviced requests
- head -> current head position

Algorithm Used:
- Shortest Seek Time First (SSTF)

==================================================
*/

/*
Program Name: SSTF Disk Scheduling
Aim: Write a C program to implement the Shortest Seek Time First (SSTF) disk scheduling algorithm.
Algorithm:
1. Read requests and head position.
2. Always service the nearest request next.
3. Sum total head movement and display order.
Compilation: gcc 11b_sstf_disk_scheduling.c -o sstf
Execution: ./sstf
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_REQ 50

int main(void)
{
    int n, head;
    int req[MAX_REQ];
    int visited[MAX_REQ] = {0};

    // Input Section
    printf("Enter number of requests (1-%d): ", MAX_REQ);
    scanf("%d", &n);

    if (n <= 0 || n > MAX_REQ) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    printf("Enter request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    // Processing Section
    int total = 0;
    int current = head;

    printf("SSTF Order: ");
    for (int done = 0; done < n; done++) {
        int minDist = 999999;
        int idx = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int dist = abs(req[i] - current);
                if (dist < minDist) {
                    minDist = dist;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            break;
        }

        printf("%d ", req[idx]);
        total += abs(req[idx] - current);
        current = req[idx];
        visited[idx] = 1;
    }

    printf("\nTotal Head Movement (SSTF): %d\n", total);

    return 0;
}
