/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Implement First-Fit contiguous memory allocation.

Logic:
1. Read block sizes and process sizes.
2. For each process, find first block that fits.
3. Allocate and update remaining block size.

Key Variables:
- block[] -> sizes of memory blocks
- process[] -> sizes of processes
- allocation[] -> assigned block index

Algorithm Used:
- First Fit

==================================================
*/

/*
Program Name: First Fit Contiguous Memory Allocation
Aim: Write a program to implement First-fit contiguous memory allocation algorithm.
Algorithm:
1. Input blocks and processes.
2. Allocate first possible block for each process.
3. Display allocation table.
Compilation: gcc 9a_first_fit_contiguous_allocation.c -o firstfit
Execution: ./firstfit
*/

#include <stdio.h>

#define MAX_B 10
#define MAX_P 10

int main(void)
{
    int b, p;
    int block[MAX_B], process[MAX_P];
    int allocation[MAX_P];

    // Input Section
    printf("Enter number of memory blocks (1-%d): ", MAX_B);
    scanf("%d", &b);
    printf("Enter sizes of blocks:\n");
    for (int i = 0; i < b; i++) {
        scanf("%d", &block[i]);
    }

    printf("Enter number of processes (1-%d): ", MAX_P);
    scanf("%d", &p);
    printf("Enter sizes of processes:\n");
    for (int i = 0; i < p; i++) {
        scanf("%d", &process[i]);
    }

    // Processing Section
    for (int i = 0; i < p; i++) {
        allocation[i] = -1;
        for (int j = 0; j < b; j++) {
            if (block[j] >= process[i]) {
                allocation[i] = j;
                block[j] -= process[i];
                break;
            }
        }
    }

    // Output Section
    printf("\nProcess\tSize\tBlock\n");
    for (int i = 0; i < p; i++) {
        if (allocation[i] != -1) {
            printf("P%d\t%d\t%d\n", i + 1, process[i], allocation[i] + 1);
        } else {
            printf("P%d\t%d\tNot Allocated\n", i + 1, process[i]);
        }
    }

    return 0;
}
