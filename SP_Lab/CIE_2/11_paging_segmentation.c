/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Demonstrate address translation using paging or segmentation.

Logic:
1. User selects paging or segmentation.
2. Paging: validate page/offset, check page table, compute physical address.
3. Segmentation: validate segment/offset against limit, compute physical address.

Key Variables:
- page_table[] -> frame number for each page (-1 means not present)
- base[], limit[] -> segment table entries

Algorithm Used:
- Paging and Segmentation translation

==================================================
*/

/*
Program Name: Paging and Segmentation Simulation
Aim: Write a C program to simulate the Paging and Segmentation techniques.
Algorithm:
1. Choose paging or segmentation.
2. Input the required table and a logical address.
3. Validate and compute physical address.
Compilation: gcc 11_paging_segmentation.c -o mem
Execution: ./mem
*/

/*
========================================
11_paging_segmentation.c

PAGING:
Physical Address =
Frame * Page Size + Offset

SEGMENTATION:
Physical Address =
Base + Offset
========================================
*/

#include <stdio.h>

#define MAX 10

int main()
{
    int choice;

    printf("1. Paging\n2. Segmentation\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    /* ---------- PAGING ---------- */

    if(choice == 1)
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

            printf("Physical Address = %d\n",
                   physical);
        }
    }

    /* ---------- SEGMENTATION ---------- */

    else if(choice == 2)
    {
        int n;
        int base[MAX], limit[MAX];
        int seg, offset;
        int physical;
        int i;

        printf("Enter number of segments: ");
        scanf("%d", &n);

        for(i = 0; i < n; i++)
        {
            printf("Base and Limit for Segment %d: ", i);
            scanf("%d %d", &base[i], &limit[i]);
        }

        printf("Enter segment number and offset: ");
        scanf("%d %d", &seg, &offset);

        if(seg >= n || offset >= limit[seg])
        {
            printf("Segmentation Fault\n");
        }
        else
        {
            physical = base[seg] + offset;

            printf("Physical Address = %d\n",
                   physical);
        }
    }

    else
    {
        printf("Invalid Choice\n");
    }

    return 0;
}

/*
Sample Input (Paging):
1
100
3
2 0 4
1 20

Sample Output (Paging):
Physical Address = 20

Sample Input (Segmentation):
2
2
1000 400
2000 300
0 200

Sample Output (Segmentation):
Physical Address = 1200
*/
