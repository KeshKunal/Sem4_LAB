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

int main()
{
    int req[20], visited[20];
    int n, head;
    int total = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence:\n");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &req[i]);
        visited[i] = 0;
    }

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nSeek Sequence: %d", head);

    for(int i = 0; i < n; i++)
    {
        int min = 9999;
        int pos = -1;

        // Find nearest request
        for(int j = 0; j < n; j++)
        {
            if(!visited[j])
            {
                int diff = abs(req[j] - head);

                if(diff < min)
                {
                    min = diff;
                    pos = j;
                }
            }
        }

        total += min;
        head = req[pos];
        visited[pos] = 1;

        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement = %d\n", total);

    return 0;
}