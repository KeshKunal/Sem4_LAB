/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Simulate segmentation address translation.

Logic:
1. Read number of segments.
2. Input base and limit for each segment.
3. Read segment number and offset.
4. Validate and compute physical address.

Key Variables:
- base[]  -> base address for each segment
- limit[] -> limit (size) for each segment

Algorithm Used:
- Segmentation address translation

==================================================
*/

/*
Program Name: Segmentation Simulation
Aim: Write a C program to simulate the Segmentation technique of memory management.
Algorithm:
1. Input segment table (base, limit).
2. Input segment number and offset.
3. Validate and compute physical address.
Compilation: gcc 7a_segmentation_memory_management.c -o seg
Execution: ./seg
*/

#include <stdio.h>

#define MAX_SEGS 20

int main(void)
{
    int segCount;
    int base[MAX_SEGS], limit[MAX_SEGS];

    // Input Section
    printf("Enter number of segments (1-%d): ", MAX_SEGS);
    scanf("%d", &segCount);

    if (segCount <= 0 || segCount > MAX_SEGS) {
        printf("Invalid number of segments.\n");
        return 1;
    }

    for (int i = 0; i < segCount; i++) {
        printf("Base and Limit for Segment %d: ", i);
        scanf("%d %d", &base[i], &limit[i]);
    }

    // Processing Section
    int seg, offset;
    printf("Enter segment number and offset: ");
    scanf("%d %d", &seg, &offset);

    if (seg < 0 || seg >= segCount || offset < 0 || offset >= limit[seg]) {
        printf("Segmentation Fault\n");
    } else {
        int physical = base[seg] + offset;
        printf("Physical Address = %d\n", physical);
    }

    return 0;
}

/*
Sample Input:
Enter number of segments (1-20): 2
Base and Limit for Segment 0: 1000 400
Base and Limit for Segment 1: 2000 300
Enter segment number and offset: 0 200

Sample Output:
Physical Address = 1200
*/
