/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Check if the system is in a safe state (Banker's Safety Algorithm).

Logic:
1. Read Allocation, Max, and Available.
2. Compute Need = Max - Allocation.
3. Find a safe sequence if possible.

Key Variables:
- allocation[][], max[][], need[][], available[]

Algorithm Used:
- Banker's Algorithm (Safety check)

==================================================
*/

/*
Program Name: Safety Algorithm (Banker's)
Aim: Write a C program to simulate Safety Algorithm to check whether the system is in a deadlock state or not.
Algorithm:
1. Input Allocation, Max, Available.
2. Compute Need.
3. Run safety algorithm to find safe sequence.
Compilation: gcc 8b_safety_algorithm_bankers.c -o safety
Execution: ./safety
*/

#include <stdio.h>

#define MAX_P 10
#define MAX_R 10

int main(void)
{
    int n, m;
    int allocation[MAX_P][MAX_R], max[MAX_P][MAX_R], need[MAX_P][MAX_R];
    int available[MAX_R];
    int finish[MAX_P] = {0};
    int safe_seq[MAX_P];
    int i, j, p, count = 0;

    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &m);

    printf("Enter Allocation matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &allocation[i][j]);

    printf("Enter Max matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &available[j]);

    // Calculate Need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - allocation[i][j];

    // Find safe sequence
    for (int k = 0; k < n; k++) {
        for (p = 0; p < n; p++) {
            if (finish[p] == 0) {
                int can_run = 1;
                for (j = 0; j < m; j++) {
                    if (need[p][j] > available[j]) {
                        can_run = 0;
                        break;
                    }
                }

                if (can_run) {
                    safe_seq[count++] = p;
                    for (j = 0; j < m; j++)
                        available[j] += allocation[p][j];
                    finish[p] = 1;
                }
            }
        }
    }

    if (count == n) {
        printf("\nSystem is in a SAFE state.\nSafe sequence: ");
        for (i = 0; i < n; i++)
            printf("P%d ", safe_seq[i]);
        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state.\n");
    }

    return 0;
}
