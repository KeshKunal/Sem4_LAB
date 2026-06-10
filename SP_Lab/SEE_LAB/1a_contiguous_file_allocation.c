/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Display a simple contiguous allocation example.
- Show the blocks occupied by each file using the user-entered start block and length.

Logic:
1. Read the file name, starting block, and length.
2. Print the contiguous block range for each file.
3. Display the file table.

Key Variables:
- start[] -> starting block for each file
- length[] -> length of each file
- name[][] -> file names

Algorithm Used:
- Direct display of the user-provided contiguous block range

==================================================
*/

/*
Program Name: Contiguous File Allocation
Aim: Write a C program to display contiguous file allocation details for files.
Algorithm:
1. Read file name, starting block, and length.
2. Store the values in arrays.
3. Print the allocated block range for each file.
Compilation: gcc 1a_contiguous_file_allocation.c -o contig
Execution: ./contig
*/

#include <stdio.h>

int main()
{
    int n;
    int start[10], length[10];
    char name[10][20]; 

    printf("Enter the number of files: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter file name: ");
        scanf("%s", name[i]);

        printf("Enter starting block: ");
        scanf("%d", &start[i]);

        printf("Enter length of file: ");
        scanf("%d", &length[i]);
    }

    printf("\n-----------------------------------------------\n");
    printf("File\tStart\tLength\tAllocated Blocks\n");
    printf("-----------------------------------------------\n");

    for (int i = 0; i < n; i++)
    {
        printf("%s\t%d\t%d\t", name[i], start[i], length[i]);

        for (int b = start[i]; b < start[i] + length[i]; b++) {
            printf("%d ", b);
        }
        printf("\n");
    }

    return 0;
}