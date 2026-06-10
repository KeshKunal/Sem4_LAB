/*
==================================================
QUICK OVERVIEW
==================================================

Purpose:
- Simulate linked file allocation technique.
- Store and display block numbers as linked chains for each file.

Approach:
1. Read number of files.
2. For each file, input: start block, end block, number of blocks used, and the block chain.
3. Display file allocation table showing each file's start, end, and allocated blocks.
4. Allow user to query and display the complete block chain for a specific file.

Key Variables:
- start[] -> starting block of each file
- end[] -> ending block of each file
- blocks[][] -> 2D array storing block chain for each file
- count[] -> number of blocks used by each file

Algorithm Used:
- Linked file allocation (blocks are linked together in a chain)

Notes:
- This program simulates file allocation without actual disk I/O.
- Input validation for block availability is not implemented in this version.

==================================================
*/

#include <stdio.h> 
 
int main() 
 { 
    int n, start[10], end[10], blocks[10][30], count[10]; 
    int file, next, current; 
 
    printf("Enter number of files: "); 
    scanf("%d", &n); 
 
    for (int i = 0; i < n; i++) { 
        printf("\nEnter start block of file-%d: ", i + 1); 
        scanf("%d", &start[i]); 
 
        printf("Enter end block of file-%d: ", i + 1); 
        scanf("%d", &end[i]); 
 
        printf("Enter number of blocks used by file-%d: ", i + 1); 
        scanf("%d", &count[i]); 
 
        printf("Enter linked blocks: "); 
        for (int j = 0; j < count[i]; j++) { 
            scanf("%d", &blocks[i][j]); 
        } 
    } 
 
    printf("\nFile\tStart\tEnd\tBlocks\n"); 
    for (int i = 0; i < n; i++) { 
 
 
        printf("%d\t%d\t%d\t", i + 1, start[i], end[i]); 
        for (int j = 0; j < count[i]; j++)  
    { 
            printf("%d ", blocks[i][j]); 
        } 
        printf("\n"); 
    } 
 
    printf("\nEnter the file number to display its chain: "); 
    scanf("%d", &file); 
    printf("\nFollowing blocks are allocated for File-%d:\n", file); 
    for (int j = 0; j < count[file - 1]; j++)  
   { 
        printf("%d -> ", blocks[file - 1][j]); 
    } 
    printf("NULL\n"); 
 
    return 0; 
}