/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Simulate paging address translation.

Logic:
1. Read page size and number of pages.
2. Input page table (frame numbers).
3. Input page number and offset.
4. Validate and compute physical address.

Key Variables:
- page_table[] -> frame number for each page

Algorithm Used:
- Paging address translation

==================================================
*/

/*
Program Name: Paging Simulation
Aim: Write a C program to simulate Paging technique of memory management.
Algorithm:
1. Input page size and page table.
2. Input page number and offset.
3. Compute physical address.
Compilation: gcc 10a_paging_memory_management.c -o paging
Execution: ./paging
*/

#include <stdio.h>

#define MAX 10

int main()
{
    int page_size, n;
    int page_table[MAX];
    int page, offset;
    int frame, physical;
    int i;

    printf("Enter page size: ");
    scanf("%d", &page_size);

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter frame number for each page:\n");

    for(i = 0; i < n; i++)
    {
        printf("Page %d: ", i);
        scanf("%d", &page_table[i]);
    }

    printf("Enter page number and offset: ");
    scanf("%d %d", &page, &offset);

    if(page >= n || offset >= page_size)
    {
        printf("Invalid Address\n");
    }
    else if(page_table[page] == -1)
    {
        printf("Page Fault\n");
    }
    else
    {
        frame = page_table[page];
        physical = frame * page_size + offset;
        printf("Physical Address = %d\n", physical);
    }

    return 0;
}
