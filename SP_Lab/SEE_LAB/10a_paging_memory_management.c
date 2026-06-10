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

#define MAX_PAGES 50

int main(void)
{
    int pageSize, numPages;
    int pageTable[MAX_PAGES];

    // Input Section
    printf("Enter page size: ");
    scanf("%d", &pageSize);
    printf("Enter number of pages (1-%d): ", MAX_PAGES);
    scanf("%d", &numPages);

    if (pageSize <= 0 || numPages <= 0 || numPages > MAX_PAGES) {
        printf("Invalid paging values.\n");
        return 1;
    }

    printf("Enter frame number for each page (use -1 for not present):\n");
    for (int i = 0; i < numPages; i++) {
        printf("Page %d -> Frame: ", i);
        scanf("%d", &pageTable[i]);
    }

    // Processing Section
    int page, offset;
    printf("Enter page number and offset: ");
    scanf("%d %d", &page, &offset);

    if (page < 0 || page >= numPages || offset < 0 || offset >= pageSize) {
        printf("Invalid Address\n");
    } else if (pageTable[page] == -1) {
        printf("Page Fault\n");
    } else {
        int physical = pageTable[page] * pageSize + offset;
        printf("Physical Address = %d\n", physical);
    }

    return 0;
}
