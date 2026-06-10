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

int main()
{
    int b, p, i, j;
    int block[MAX_B], process[MAX_P];
    int allocation[MAX_P];
    int temp_block[MAX_B];
    int totalHole = 0;

    printf("Enter number of memory blocks: ");
    scanf("%d", &b);

    printf("Enter sizes of blocks:\n");
    for(i = 0; i < b; i++)
    {
        scanf("%d", &block[i]);
        temp_block[i] = block[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &p);

    printf("Enter sizes of processes:\n");
    for(i = 0; i < p; i++)
    {
        scanf("%d", &process[i]);
        allocation[i] = -1;
    }

    for(i = 0; i < p; i++)
    {
        for(j = 0; j < b; j++)
        {
            if(temp_block[j] >= process[i])
            {
                allocation[i] = j;
                temp_block[j] -= process[i];
                break;
            }
        }
    }

    printf("\nProcess\tSize\tBlock\n");

    for(i = 0; i < p; i++)
    {
        printf("P%d\t%d\t", i + 1, process[i]);

        if(allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    // Calculate Total Hole Size
    for(i = 0; i < b; i++)
    {
        totalHole += temp_block[i];
    }

    printf("\nTotal Hole Size = %d\n", totalHole);

    return 0;
}