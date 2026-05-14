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

int main()
{
    int req[20], n, head, disk, dir;
    int i, j, temp;
    int fcfs = 0, scan = 0;

    // Input
    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &req[i]);
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &disk);

    printf("Enter direction (0-left, 1-right): ");
    scanf("%d", &dir);

    // -------- FCFS --------
    int current = head;

    for(i = 0; i < n; i++)
    {
        if(req[i] > current)
            fcfs += req[i] - current;
        else
            fcfs += current - req[i];

        current = req[i];
    }

    // -------- SORT --------
    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(req[j] > req[j + 1])
            {
                temp = req[j];
                req[j] = req[j + 1];
                req[j + 1] = temp;
            }
        }
    }

    // Find head position index
    int pos = 0;

    while(pos < n && req[pos] < head)
    {
        pos++;
    }

    current = head;

    // -------- SCAN RIGHT --------
    if(dir == 1)
    {
        for(i = pos; i < n; i++)
        {
            scan += req[i] - current;
            current = req[i];
        }

        scan += (disk - 1) - current;
        current = disk - 1;

        for(i = pos - 1; i >= 0; i--)
        {
            scan += current - req[i];
            current = req[i];
        }
    }

    // -------- SCAN LEFT --------
    else
    {
        for(i = pos - 1; i >= 0; i--)
        {
            scan += current - req[i];
            current = req[i];
        }

        scan += current;
        current = 0;

        for(i = pos; i < n; i++)
        {
            scan += req[i] - current;
            current = req[i];
        }
    }

    // Output
    printf("\nFCFS Total Head Movement = %d\n", fcfs);
    printf("SCAN Total Head Movement = %d\n", scan);

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
