/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Simulate Optimal page replacement.

Logic:
1. For each page miss, replace the page used farthest in future.
2. If a page is never used again, replace it immediately.
3. Count page faults.

Key Variables:
- frames[] -> current pages in memory
- farthest -> farthest future use index

Algorithm Used:
- Optimal page replacement

==================================================
*/

/*
Program Name: Optimal Page Replacement
Aim: Write a C program to simulate Optimal page replacement algorithm.
Algorithm:
1. Read reference string and frame count.
2. Apply Optimal replacement.
3. Display page faults.
Compilation: gcc 6b_page_replacement_optimal.c -o opt
Execution: ./opt
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
                int farthest = -1;
                int index = -1;
                for (int j = 0; j < f; j++) {
                    int next = -1;
                    for (int k = i + 1; k < n; k++) {
                        if (frames[j] == pages[k]) {
                            next = k;
                            break;
                        }
                    }
                    if (next == -1) {
                        index = j;
                        break;
                    }
                    if (next > farthest) {
                        farthest = next;
                        index = j;
                    }
                }
                frames[index] = pages[i];
            }
        }
    }

    printf("Optimal Page Faults: %d\n", faults);
    return 0;
}
