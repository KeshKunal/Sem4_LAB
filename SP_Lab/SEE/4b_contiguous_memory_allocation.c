#include <stdio.h>

#define MAX_B 20
#define MAX_P 20

void copy_array(int dest[], int src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

void print_allocation(const char *title, int np, int processSize[], int allocation[]) {
    printf("\n%s\n", title);
    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < np; i++) {
        if (allocation[i] == -1) {
            printf("P%d\t%d\tNot Allocated\n", i + 1, processSize[i]);
        } else {
            printf("P%d\t%d\t%d\n", i + 1, processSize[i], allocation[i] + 1);
        }
    }
}

void first_fit(int nb, int blockSize[], int np, int processSize[], int allocation[]) {
    for (int i = 0; i < np; i++) {
        allocation[i] = -1;
        for (int j = 0; j < nb; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
}

void best_fit(int nb, int blockSize[], int np, int processSize[], int allocation[]) {
    for (int i = 0; i < np; i++) {
        allocation[i] = -1;
        int bestIdx = -1;
        int minRem = 999999;
        for (int j = 0; j < nb; j++) {
            if (blockSize[j] >= processSize[i]) {
                int rem = blockSize[j] - processSize[i];
                if (rem < minRem) {
                    minRem = rem;
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
}

void worst_fit(int nb, int blockSize[], int np, int processSize[], int allocation[]) {
    for (int i = 0; i < np; i++) {
        allocation[i] = -1;
        int worstIdx = -1;
        int maxRem = -1;
        for (int j = 0; j < nb; j++) {
            if (blockSize[j] >= processSize[i]) {
                int rem = blockSize[j] - processSize[i];
                if (rem > maxRem) {
                    maxRem = rem;
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
}

int main(void) {
    int nb, np;
    int blockSize[MAX_B], processSize[MAX_P];

    printf("Contiguous Memory Allocation (First/Best/Worst Fit)\n");
    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);
    if (nb <= 0 || nb > MAX_B) {
        printf("Invalid number of blocks.\n");
        return 1;
    }

    printf("Enter block sizes:\n");
    for (int i = 0; i < nb; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter number of processes: ");
    scanf("%d", &np);
    if (np <= 0 || np > MAX_P) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    printf("Enter process sizes:\n");
    for (int i = 0; i < np; i++) {
        scanf("%d", &processSize[i]);
    }

    int blocks1[MAX_B], blocks2[MAX_B], blocks3[MAX_B];
    int alloc1[MAX_P], alloc2[MAX_P], alloc3[MAX_P];

    copy_array(blocks1, blockSize, nb);
    copy_array(blocks2, blockSize, nb);
    copy_array(blocks3, blockSize, nb);

    first_fit(nb, blocks1, np, processSize, alloc1);
    best_fit(nb, blocks2, np, processSize, alloc2);
    worst_fit(nb, blocks3, np, processSize, alloc3);

    print_allocation("First Fit", np, processSize, alloc1);
    print_allocation("Best Fit", np, processSize, alloc2);
    print_allocation("Worst Fit", np, processSize, alloc3);

    return 0;
}
