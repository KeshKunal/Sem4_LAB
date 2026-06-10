/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Simulate Round Robin CPU scheduling.

Logic:
1. Read burst times and time quantum.
2. Repeatedly allocate CPU in time slices.
3. Compute completion, turnaround, waiting times.

Key Variables:
- bt[] -> burst time
- rt[] -> remaining time
- ct[] -> completion time

Algorithm Used:
- Round Robin Scheduling

==================================================
*/

/*
Program Name: Round Robin Scheduling
Aim: Write a C program to simulate Round-Robin CPU scheduling algorithm.
Algorithm:
1. Read number of processes, burst times, and time quantum.
2. Simulate round robin until all are done.
3. Compute CT, TAT, WT and averages.
Compilation: gcc 7b_round_robin_scheduling.c -o rr
Execution: ./rr
*/

#include <stdio.h>

#define MAX_P 10

int main()
{
    int n, tq, time = 0;
    int bt[MAX_P], rt[MAX_P];
    int wt[MAX_P], tat[MAX_P];
    int i, remaining;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    remaining = n;

    for (i = 0; i < n; i++)
    {
        printf("Burst time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    while (remaining > 0)
    {
        for (i = 0; i < n; i++)
        {
            if (rt[i] > 0)
            {
                if (rt[i] > tq)
                {
                    time += tq;
                    rt[i] -= tq;
                }
                else
                {
                    time += rt[i];
                    wt[i] = time - bt[i];
                    rt[i] = 0;
                    remaining--;
                }
            }
        }
    }

    printf("\nProcess\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
