#include <stdio.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10

int fifo_faults(int pages[], int n, int frames) {
    int frame[MAX_FRAMES];
    int idx = 0, faults = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int hit = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                hit = 1;
                break;
            }
        }
        if (!hit) {
            frame[idx] = pages[i];
            idx = (idx + 1) % frames;
            faults++;
        }
    }
    return faults;
}

int lru_faults(int pages[], int n, int frames) {
    int frame[MAX_FRAMES];
    int lastUsed[MAX_FRAMES];
    int faults = 0;

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

    return faults;
}

int optimal_faults(int pages[], int n, int frames) {
    int frame[MAX_FRAMES];
    int faults = 0;

    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int hit = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                hit = 1;
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
                int farthest = -1;
                int idx = -1;
                for (int j = 0; j < frames; j++) {
                    int nextUse = -1;
                    for (int k = i + 1; k < n; k++) {
                        if (pages[k] == frame[j]) {
                            nextUse = k;
                            break;
                        }
                    }
                    if (nextUse == -1) {
                        idx = j;
                        break;
                    }
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        idx = j;
                    }
                }
                replace = idx;
            }

            frame[replace] = page;
            faults++;
        }
    }

    return faults;
}

int main(void) {
    int n, frames;
    int pages[MAX_PAGES];

    printf("Page Replacement Algorithms (FIFO, LRU, Optimal)\n");
    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX_PAGES) {
        printf("Invalid number of pages.\n");
        return 1;
    }

    printf("Enter the reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &frames);
    if (frames <= 0 || frames > MAX_FRAMES) {
        printf("Invalid number of frames.\n");
        return 1;
    }

    int fifo = fifo_faults(pages, n, frames);
    int lru = lru_faults(pages, n, frames);
    int opt = optimal_faults(pages, n, frames);

    printf("\nFIFO  - Page Faults: %d, Hits: %d\n", fifo, n - fifo);
    printf("LRU   - Page Faults: %d, Hits: %d\n", lru, n - lru);
    printf("OPT   - Page Faults: %d, Hits: %d\n", opt, n - opt);

    return 0;
}
