/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Implement disk scheduling using FCFS and SCAN.

Logic:
1. Read disk requests, head position, disk size, direction.
2. FCFS: service in given order.
3. SCAN: move in one direction to end, then reverse.

Key Variables:
- req[] -> disk requests
- head -> current head position
- total -> total head movement

Algorithm Used:
- FCFS and SCAN disk scheduling

==================================================
*/

/*
Program Name: Disk Scheduling (FCFS and SCAN)
Aim: Implementation of Disk Scheduling using FCFS and SCAN algorithms.
Algorithm:
1. Read requests and head.
2. Compute FCFS movement.
3. Compute SCAN movement based on direction.
Compilation: gcc 10_disk_scheduling_fcfs_scan.c -o disk
Execution: ./disk
*/

#include <stdio.h>

#define MAX_REQ 20

static void bubble_sort(int a[], int n)
{
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main(void)
{
    int req[MAX_REQ], n, i;
    int head, disk_size, direction;
    int total_fcfs = 0, total_scan = 0;

    // Input Section
    printf("Enter number of requests (1-%d): ", MAX_REQ);
    scanf("%d", &n);
    printf("Enter request sequence:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &req[i]);
    }
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size (max cylinder number): ");
    scanf("%d", &disk_size);
    printf("Enter direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    // Processing Section - FCFS
    int current = head;
    for (i = 0; i < n; i++) {
        int diff = req[i] - current;
        if (diff < 0) diff = -diff;
        total_fcfs += diff;
        current = req[i];
    }

    // Processing Section - SCAN
    int sorted[MAX_REQ];
    for (i = 0; i < n; i++) {
        sorted[i] = req[i];
    }
    bubble_sort(sorted, n);

    int idx = 0;
    while (idx < n && sorted[idx] < head) {
        idx++;
    }

    current = head;
    if (direction == 1) {
        /* move right */
        for (i = idx; i < n; i++) {
            int diff = sorted[i] - current;
            if (diff < 0) diff = -diff;
            total_scan += diff;
            current = sorted[i];
        }
        if (current != disk_size - 1) {
            total_scan += (disk_size - 1 - current);
            current = disk_size - 1;
        }
        for (i = idx - 1; i >= 0; i--) {
            int diff = current - sorted[i];
            total_scan += diff;
            current = sorted[i];
        }
    } else {
        /* move left */
        for (i = idx - 1; i >= 0; i--) {
            int diff = current - sorted[i];
            total_scan += diff;
            current = sorted[i];
        }
        if (current != 0) {
            total_scan += current;
            current = 0;
        }
        for (i = idx; i < n; i++) {
            int diff = sorted[i] - current;
            total_scan += diff;
            current = sorted[i];
        }
    }

    // Output Section
    printf("FCFS Total Head Movement: %d\n", total_fcfs);
    printf("SCAN Total Head Movement: %d\n", total_scan);

    /* Time Complexity: O(n^2) due to bubble sort. */
    return 0;
}

/*
Sample Input:
Enter number of requests (1-20): 8
Enter request sequence:
98 183 37 122 14 124 65 67
Enter initial head position: 53
Enter disk size (max cylinder number): 200
Enter direction (0 for left, 1 for right): 1

Sample Output:
FCFS Total Head Movement: 640
SCAN Total Head Movement: 331
*/
