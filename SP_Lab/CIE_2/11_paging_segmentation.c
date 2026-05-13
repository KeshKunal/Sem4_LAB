/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Demonstrate paging and segmentation address translation.

Logic:
1. Paging: use page table to map page -> frame.
2. Segmentation: use base and limit for each segment.
3. Validate offset and compute physical address.

Key Variables:
- page_table[] -> frame number for each page
- base[], limit[] -> segment table

Algorithm Used:
- Paging and Segmentation translation

==================================================
*/

/*
Program Name: Paging and Segmentation Simulation
Aim: Write a C program to simulate the Paging and Segmentation techniques.
Algorithm:
1. Input paging details and translate a logical address.
2. Input segmentation details and translate a logical address.
Compilation: gcc 11_paging_segmentation.c -o mem
Execution: ./mem
*/

#include <stdio.h>

#define MAX_PAGES 10
#define MAX_SEGS 10

int main(void)
{
    int page_size, num_pages;
    int page_table[MAX_PAGES];
    int page, offset, frame, physical;

    int num_segs;
    int base[MAX_SEGS], limit[MAX_SEGS];
    int seg, off;

    // Input Section - Paging
    printf("Enter page size: ");
    scanf("%d", &page_size);
    printf("Enter number of pages (1-%d): ", MAX_PAGES);
    scanf("%d", &num_pages);
    printf("Enter page table (frame number for each page, -1 if not present):\n");
    for (int i = 0; i < num_pages; i++) {
        scanf("%d", &page_table[i]);
    }
    printf("Enter logical address (page number and offset): ");
    scanf("%d %d", &page, &offset);

    // Processing Section - Paging
    if (page < 0 || page >= num_pages || offset < 0 || offset >= page_size) {
        printf("Invalid paging logical address.\n");
    } else if (page_table[page] == -1) {
        printf("Page fault: page not in memory.\n");
    } else {
        frame = page_table[page];
        physical = frame * page_size + offset;
        // Output Section
        printf("Paging Physical Address: %d\n", physical);
    }

    // Input Section - Segmentation
    printf("\nEnter number of segments (1-%d): ", MAX_SEGS);
    scanf("%d", &num_segs);
    printf("Enter base and limit for each segment:\n");
    for (int i = 0; i < num_segs; i++) {
        scanf("%d %d", &base[i], &limit[i]);
    }
    printf("Enter logical address (segment number and offset): ");
    scanf("%d %d", &seg, &off);

    // Processing Section - Segmentation
    if (seg < 0 || seg >= num_segs || off < 0 || off >= limit[seg]) {
        printf("Invalid segmentation logical address.\n");
    } else {
        physical = base[seg] + off;
        // Output Section
        printf("Segmentation Physical Address: %d\n", physical);
    }

    /* Time Complexity: O(1) per address translation. */
    return 0;
}

/*
Sample Input:
Enter page size: 100
Enter number of pages (1-10): 3
Enter page table (frame number for each page, -1 if not present):
2 0 4
Enter logical address (page number and offset): 1 20

Enter number of segments (1-10): 2
Enter base and limit for each segment:
1000 400
2000 300
Enter logical address (segment number and offset): 0 200

Sample Output:
Paging Physical Address: 20
Segmentation Physical Address: 1200
*/
