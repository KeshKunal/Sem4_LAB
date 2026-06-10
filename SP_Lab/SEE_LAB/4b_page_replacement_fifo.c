/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Simulate FIFO page replacement.

Logic:
1. Maintain frame queue pointer.
2. If page miss, replace oldest frame.
3. Count page faults.

Key Variables:
- frames[] -> current pages in memory
- pointer -> next frame to replace

Algorithm Used:
- FIFO page replacement

==================================================
*/

/*
Program Name: FIFO Page Replacement
Aim: Write a C program to simulate First-in-First-out (FIFO) page replacement algorithm.
Algorithm:
1. Read reference string and frame count.
2. Apply FIFO replacement.
3. Display page faults.
Compilation: gcc 4b_page_replacement_fifo.c -o fifo
Execution: ./fifo
*/

#include <stdio.h>

#define MAX_PAGES 30
#define MAX_FRAMES 10

int main(void)
{
    int pages[MAX_PAGES];
    int frames[MAX_FRAMES];
    int n, f;
    int faults = 0;

    printf("Enter length of reference string (1-%d): ", MAX_PAGES);
    scanf("%d", &n);
    printf("Enter reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter number of frames (1-%d): ", MAX_FRAMES);
    scanf("%d", &f);

    for (int i = 0; i < f; i++) {
        frames[i] = -1;
    }

    int pointer = 0;
    int filled = 0;
    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if (!hit) {
            faults++;
            if (filled < f) {
                frames[filled++] = pages[i];
            } else {
                frames[pointer] = pages[i];
                pointer = (pointer + 1) % f;
            }
        }
    }

    printf("FIFO Page Faults: %d\n", faults);
    return 0;
}
