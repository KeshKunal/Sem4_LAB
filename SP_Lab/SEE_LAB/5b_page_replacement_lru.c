/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Simulate LRU page replacement.

Logic:
1. Track last used time for each frame.
2. On page miss, replace least recently used frame.
3. Count page faults.

Key Variables:
- frame[] -> current pages
- lastUsed[] -> last access time for each frame

Algorithm Used:
- Least Recently Used (LRU)

==================================================
*/

/*
Program Name: LRU Page Replacement
Aim: Write a C program to simulate Least Recently Used (LRU) page replacement algorithm.
Algorithm:
1. Read reference string and frame count.
2. Apply LRU replacement.
3. Display page faults.
Compilation: gcc 5b_page_replacement_lru.c -o lru
Execution: ./lru
*/

#include <stdio.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10

int main(void)
{
    int pages[MAX_PAGES];
    int frame[MAX_FRAMES];
    int lastUsed[MAX_FRAMES];
    int n, frames;
    int faults = 0;

    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    printf("Enter the reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        lastUsed[i] = -1;
    }

    for (int t = 0; t < n; t++) {
        int page = pages[t];
        int hit = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                hit = 1;
                lastUsed[j] = t;
                break;
            }
        }

        if (!hit) {
            int replace = -1;
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    replace = j;
                    break;
                }
            }
            if (replace == -1) {
                int lruIdx = 0;
                for (int j = 1; j < frames; j++) {
                    if (lastUsed[j] < lastUsed[lruIdx]) {
                        lruIdx = j;
                    }
                }
                replace = lruIdx;
            }
            frame[replace] = page;
            lastUsed[replace] = t;
            faults++;
        }
    }

    printf("LRU Page Faults: %d\n", faults);
    return 0;
}
