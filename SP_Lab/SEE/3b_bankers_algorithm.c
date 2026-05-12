#include <stdio.h>

#define MAX_P 10
#define MAX_R 10

int main(void) {
    int n, m;
    int alloc[MAX_P][MAX_R];
    int max[MAX_P][MAX_R];
    int need[MAX_P][MAX_R];
    int avail[MAX_R];
    int finish[MAX_P] = {0};
    int safeSeq[MAX_P];

    printf("Banker's Algorithm\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    if (n <= 0 || n > MAX_P || m <= 0 || m > MAX_R) {
        printf("Invalid input sizes.\n");
        return 1;
    }

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter Max matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    printf("Enter Available resources:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    int count = 0;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int canRun = 1;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canRun = 0;
                        break;
                    }
                }
                if (canRun) {
                    for (int j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                    }
                    finish[i] = 1;
                    safeSeq[count++] = i;
                    found = 1;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    if (count == n) {
        printf("System is in a safe state.\nSafe sequence: ");
        for (int i = 0; i < n; i++) {
            printf("P%d ", safeSeq[i] + 1);
        }
        printf("\n");
    } else {
        printf("System is NOT in a safe state.\n");
    }

    return 0;
}
