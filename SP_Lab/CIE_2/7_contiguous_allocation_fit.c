/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Implement contiguous memory allocation strategies.
- First Fit, Best Fit, and Worst Fit.

Logic:
1. Read block sizes and process sizes.
2. Run First Fit allocation.
3. Run Best Fit allocation.
4. Run Worst Fit allocation.

Key Variables:
- block[] -> sizes of memory blocks
- process[] -> sizes of processes
- allocation[] -> block index for each process

Algorithm Used:
- First Fit, Best Fit, Worst Fit

==================================================
*/

/*
Program Name: Contiguous Allocation (First Fit, Best Fit, Worst Fit)
Aim: Write a program to implement the contiguous memory strategies algorithms: First Fit, Best Fit, and Worst Fit for contiguous allocation.
Algorithm:
1. Read blocks and processes.
2. Apply First Fit, Best Fit, Worst Fit.
3. Display allocations.
Compilation: gcc 7_contiguous_allocation_fit.c -o fit
Execution: ./fit
*/

#include <stdio.h>

#define MAX_B 10
#define MAX_P 10

int main(void)
{
    int b, p, i, j;
    int block[MAX_B], process[MAX_P];
    int alloc_ff[MAX_P], alloc_bf[MAX_P], alloc_wf[MAX_P];
    int temp[MAX_B];

    // Input Section
    printf("Enter number of memory blocks (1-%d): ", MAX_B);
    scanf("%d", &b);
    printf("Enter sizes of blocks:\n");
    for (i = 0; i < b; i++) {
        scanf("%d", &block[i]);
    }

    printf("Enter number of processes (1-%d): ", MAX_P);
    scanf("%d", &p);
    printf("Enter sizes of processes:\n");
    for (i = 0; i < p; i++) {
        scanf("%d", &process[i]);
    }

    // Processing Section - First Fit
    for (i = 0; i < p; i++) {
        alloc_ff[i] = -1;
    }
    for (i = 0; i < b; i++) {
        temp[i] = block[i];
    }
    for (i = 0; i < p; i++) {
        for (j = 0; j < b; j++) {
            if (temp[j] >= process[i]) {
                alloc_ff[i] = j;
                temp[j] -= process[i];
                break;
            }
        }
    }

    // Processing Section - Best Fit
    for (i = 0; i < p; i++) {
        alloc_bf[i] = -1;
    }
    for (i = 0; i < b; i++) {
        temp[i] = block[i];
    }
    for (i = 0; i < p; i++) {
        int best = -1;
        for (j = 0; j < b; j++) {
            if (temp[j] >= process[i]) {
                if (best == -1 || temp[j] < temp[best]) {
                    best = j;
                }
            }
        }
        if (best != -1) {
            alloc_bf[i] = best;
            temp[best] -= process[i];
        }
    }

    // Processing Section - Worst Fit
    for (i = 0; i < p; i++) {
        alloc_wf[i] = -1;
    }
    for (i = 0; i < b; i++) {
        temp[i] = block[i];
    }
    for (i = 0; i < p; i++) {
        int worst = -1;
        for (j = 0; j < b; j++) {
            if (temp[j] >= process[i]) {
                if (worst == -1 || temp[j] > temp[worst]) {
                    worst = j;
                }
            }
        }
        if (worst != -1) {
            alloc_wf[i] = worst;
            temp[worst] -= process[i];
        }
    }

    // Output Section
    printf("\nFIRST FIT Allocation:\n");
    for (i = 0; i < p; i++) {
        if (alloc_ff[i] != -1) {
            printf("Process %d -> Block %d\n", i + 1, alloc_ff[i] + 1);
        } else {
            printf("Process %d -> Not Allocated\n", i + 1);
        }
    }

    printf("\nBEST FIT Allocation:\n");
    for (i = 0; i < p; i++) {
        if (alloc_bf[i] != -1) {
            printf("Process %d -> Block %d\n", i + 1, alloc_bf[i] + 1);
        } else {
            printf("Process %d -> Not Allocated\n", i + 1);
        }
    }

    printf("\nWORST FIT Allocation:\n");
    for (i = 0; i < p; i++) {
        if (alloc_wf[i] != -1) {
            printf("Process %d -> Block %d\n", i + 1, alloc_wf[i] + 1);
        } else {
            printf("Process %d -> Not Allocated\n", i + 1);
        }
    }

    /* Time Complexity: O(p * b) for each strategy. */
    return 0;
}

/*
Sample Input:
Enter number of memory blocks (1-10): 3
Enter sizes of blocks:
100 500 200
Enter number of processes (1-10): 4
Enter sizes of processes:
212 417 112 426

Sample Output:
FIRST FIT Allocation:
Process 1 -> Block 2
Process 2 -> Not Allocated
Process 3 -> Block 3
Process 4 -> Not Allocated

BEST FIT Allocation:
Process 1 -> Block 2
Process 2 -> Not Allocated
Process 3 -> Block 3
Process 4 -> Not Allocated

WORST FIT Allocation:
Process 1 -> Block 2
Process 2 -> Not Allocated
Process 3 -> Block 3
Process 4 -> Not Allocated
*/
