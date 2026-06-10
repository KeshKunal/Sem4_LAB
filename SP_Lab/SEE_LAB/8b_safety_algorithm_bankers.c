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
    int allocation[MAX_P][MAX_R];
    int max[MAX_P][MAX_R];
    int need[MAX_P][MAX_R];
    int available[MAX_R];
    int finish[MAX_P] = {0};
    int safe_seq[MAX_P];
    int count = 0;

    // Input Section
    printf("Enter number of processes (1-%d): ", MAX_P);
    scanf("%d", &n);
    printf("Enter number of resource types (1-%d): ", MAX_R);
    scanf("%d", &m);

    printf("Enter Allocation matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Max matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("Enter Available resources (%d values):\n", m);
    for (int j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }

    // Processing Section
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int can_run = 1;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        can_run = 0;
                        break;
                    }
                }
                if (can_run) {
                    for (int j = 0; j < m; j++) {
                        available[j] += allocation[i][j];
                    }
                    finish[i] = 1;
                    safe_seq[count++] = i;
                    found = 1;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    // Output Section
    if (count == n) {
        printf("System is in SAFE state.\nSafe sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safe_seq[i]);
        }
        printf("\n");
    } else {
        printf("System is NOT in safe state.\n");
    }

    return 0;
}
