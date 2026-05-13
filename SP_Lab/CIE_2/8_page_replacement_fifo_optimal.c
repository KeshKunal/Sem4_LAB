/*
==================================================
MEMORY MAP / QUICK REVISION
==================================================

Goal:
- Simulate page replacement algorithms.
- FIFO and Optimal.

Logic:
1. Read reference string and frame count.
2. Run FIFO and count page faults.
3. Run Optimal and count page faults.

Key Variables:
- frames[] -> current pages in memory
- faults -> number of page faults

Algorithm Used:
- FIFO and Optimal page replacement

==================================================
*/

/*
Program Name: Page Replacement (FIFO and Optimal)
Aim: Write a program to implement Page replacement algorithms: FIFO and Optimal
Algorithm:
1. Input reference string and frames.
2. Apply FIFO replacement.
3. Apply Optimal replacement.
Compilation: gcc 8_page_replacement_fifo_optimal.c -o page
Execution: ./page
*/

#include <stdio.h>

#define MAX_PAGES 30
#define MAX_FRAMES 10

int main(void)
{
    int pages[MAX_PAGES];
    int frames[MAX_FRAMES];
    int n, f, i, j, k;
    int faults_fifo = 0, faults_opt = 0;

    // Input Section
    printf("Enter length of reference string (1-%d): ", MAX_PAGES);
    scanf("%d", &n);
    printf("Enter reference string:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter number of frames (1-%d): ", MAX_FRAMES);
    scanf("%d", &f);

    // Processing Section - FIFO
    for (i = 0; i < f; i++) {
        frames[i] = -1;
    }
    int pointer = 0;
    int filled = 0;
    for (i = 0; i < n; i++) {
        int hit = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if (!hit) {
            faults_fifo++;
            if (filled < f) {
                frames[filled++] = pages[i];
            } else {
                frames[pointer] = pages[i];
                pointer = (pointer + 1) % f;
            }
        }
    }

    // Processing Section - Optimal
    for (i = 0; i < f; i++) {
        frames[i] = -1;
    }
    filled = 0;
    for (i = 0; i < n; i++) {
        int hit = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if (!hit) {
            faults_opt++;
            if (filled < f) {
                frames[filled++] = pages[i];
            } else {
                int farthest = -1;
                int index = -1;
                for (j = 0; j < f; j++) {
                    int next = -1;
                    for (k = i + 1; k < n; k++) {
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

    // Output Section
    printf("FIFO Page Faults: %d\n", faults_fifo);
    printf("Optimal Page Faults: %d\n", faults_opt);

    /* Time Complexity: FIFO O(n*f), Optimal O(n*n*f) in worst case. */
    return 0;
}

/*
Sample Input:
Enter length of reference string (1-30): 12
Enter reference string:
1 2 3 4 1 2 5 1 2 3 4 5
Enter number of frames (1-10): 3

Sample Output:
FIFO Page Faults: 9
Optimal Page Faults: 7
*/
