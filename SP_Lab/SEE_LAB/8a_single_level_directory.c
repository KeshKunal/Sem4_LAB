/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Simulate single-level directory organization.

Logic:
1. Store all file names in a single list.
2. Support create, delete, search, display.

Key Variables:
- files[] -> list of file names
- fileCount -> number of files

Algorithm Used:
- Single-level directory simulation

==================================================
*/

/*
Program Name: Single-Level Directory Organization
Aim: Write a C program to simulate the Single-level directory organization technique.
Algorithm:
1. Create a file list.
2. Support create, delete, search, display operations.
Compilation: gcc 8a_single_level_directory.c -o dir1
Execution: ./dir1
*/

#include <stdio.h>
#include <string.h>

#define MAX_FILES 50
#define MAX_NAME_LEN 20

int main()
{
    char files[MAX_FILES][MAX_NAME_LEN];
    int n, i, found = 0;
    char search[MAX_NAME_LEN];

    printf("Enter number of files: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("Enter file %d name: ", i + 1);
        scanf("%s", files[i]);
    }

    // Display structure
    printf("\nSingle Level Directory Structure:\n\n");
    printf("Root\n");
    printf(" |\n");

    for(i = 0; i < n; i++)
    {
        if(i == n - 1)
            printf(" `-- %s\n", files[i]);
        else
            printf(" +-- %s\n", files[i]);
    }

    // Search operation
    printf("\nEnter file name to search: ");
    scanf("%s", search);

    for(i = 0; i < n; i++)
    {
        if(strcmp(files[i], search) == 0)
        {
            found = 1;
            break;
        }
    }

    if(found)
        printf("File '%s' found in Root directory.\n", search);
    else
        printf("File '%s' not found.\n", search);

    return 0;
}