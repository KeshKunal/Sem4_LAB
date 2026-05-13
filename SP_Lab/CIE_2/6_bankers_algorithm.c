/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Check if system is in safe state using Banker's Algorithm.
- Find a safe sequence if possible.

Logic:
1. Read Allocation, Max, and Available.
2. Compute Need = Max - Allocation.
3. Repeatedly find a process whose Need <= Available.
4. If all processes finish, system is safe.

Key Variables:
- allocation[][] -> current allocated resources
- max[][] -> maximum required resources
- need[][] -> remaining required resources
- available[] -> available resources

Algorithm Used:
- Banker's Algorithm (Safety check)

==================================================
*/

/*
Program Name: Bankers Algorithm for Deadlock Avoidance
Aim: Write a C program to simulate Bankers Algorithm for Deadlock Avoidance
Algorithm:
1. Input matrices Allocation, Max and vector Available.
2. Compute Need matrix.
3. Find safe sequence using safety algorithm.
Compilation: gcc 6_bankers_algorithm.c -o banker
Execution: ./banker
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
    int finish[MAX_P] = {0};  // tracks completed process
    int safe_seq[MAX_P];
    int i, j, count = 0, found;

    // Input Section
    printf("Enter number of processes (1-%d): ", MAX_P);
    scanf("%d", &n);
    printf("Enter number of resource types (1-%d): ", MAX_R);
    scanf("%d", &m);

    printf("Enter Allocation matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Max matrix (%d x %d):\n", n, m);
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available resources (%d values):\n", m);
    for (j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }

    // Processing Section
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    while (count < n) {
        found = 0;  //Did we find at least one runnable process?
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                int can_run = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        can_run = 0;
                        break;
                    }
                }
                if (can_run) {
                    for (j = 0; j < m; j++) {
                        available[j] += allocation[i][j];
                    }
                    safe_seq[count++] = i;
                    finish[i] = 1;
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
        for (i = 0; i < n; i++) {
            printf("P%d ", safe_seq[i]);
        }
        printf("\n");
    } else {
        printf("System is NOT in safe state.\n");
    }

    /* Time Complexity: O(n^2 * m) in worst case. */
    return 0;
}

/*
Sample Input:
Enter number of processes (1-10): 3
Enter number of resource types (1-10): 3
Enter Allocation matrix (3 x 3):
0 1 0
2 0 0
3 0 2
Enter Max matrix (3 x 3):
7 5 3
3 2 2
9 0 2
Enter Available resources (3 values):
3 3 2

Sample Output:
System is in SAFE state.
Safe sequence: P1 P0 P2
*/
