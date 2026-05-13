/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Simulate LRU page replacement using a stack.
- Most recently used page stays on top.

Logic:
1. Read reference string and frame count.
2. If page hit, move to top of stack.
3. If miss, replace least recently used (bottom).

Key Variables:
- stack[] -> pages in memory (LRU at index 0)
- faults -> page fault count

Algorithm Used:
- LRU page replacement using stack

==================================================
*/

/*
Program Name: LRU Page Replacement using Stack
Aim: Write a program to demonstrate LRU replacement algorithm using Stack.
Algorithm:
1. Read reference string and frame count.
2. Maintain stack of recent pages.
3. Replace least recently used page on fault.
Compilation: gcc 9_lru_stack.c -o lru
Execution: ./lru
*/

#include <stdio.h>

#define MAX_PAGES 30
#define MAX_FRAMES 10

int main(void)
{
    int pages[MAX_PAGES];
    int stack[MAX_FRAMES];
    int n, f, i, j;
    int count = 0;
    int faults = 0;

    // Input Section
    printf("Enter length of reference string (1-%d): ", MAX_PAGES);
    scanf("%d", &n);
    printf("Enter reference string:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter number of frames (1-%d): ", MAX_FRAMES);
    scanf("%d", &f);

    // Processing Section
    for (i = 0; i < f; i++) {
        stack[i] = -1;
    }

    for (i = 0; i < n; i++) {
        int pos = -1;
        for (j = 0; j < count; j++) {
            if (stack[j] == pages[i]) {
                pos = j;
                break;
            }
        }

        if (pos != -1) {
            /* Page hit: move to top */
            int temp = stack[pos];
            for (j = pos; j < count - 1; j++) {
                stack[j] = stack[j + 1];
            }
            stack[count - 1] = temp;
        } else {
            /* Page fault */
            faults++;
            if (count < f) {
                stack[count++] = pages[i];
            } else {
                for (j = 0; j < f - 1; j++) {
                    stack[j] = stack[j + 1];
                }
                stack[f - 1] = pages[i];
            }
        }
    }

    // Output Section
    printf("LRU Page Faults: %d\n", faults);

    /* Time Complexity: O(n*f). */
    return 0;
}

/*
Sample Input:
Enter length of reference string (1-30): 12
Enter reference string:
1 2 3 4 1 2 5 1 2 3 4 5
Enter number of frames (1-10): 3

Sample Output:
LRU Page Faults: 10
*/
