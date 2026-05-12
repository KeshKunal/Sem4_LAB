#include <stdio.h>

#define MAX_P 20

void cpu_virtualization(void) {
    int n, tq;
    int bt[MAX_P], rt[MAX_P], ct[MAX_P], tat[MAX_P], wt[MAX_P];

    printf("\nCPU Virtualization (Round Robin)\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);
    if (n <= 0 || n > MAX_P) {
        printf("Invalid number of processes.\n");
        return;
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);
    if (tq <= 0) {
        printf("Invalid time quantum.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("Burst time of P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
        ct[i] = 0;
    }

    int time = 0;
    int done;
    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0) {
                done = 0;
                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                }
            }
        }
    } while (!done);

    double totalWT = 0, totalTAT = 0;
    printf("\nProcess\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i];
        wt[i] = tat[i] - bt[i];
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, bt[i], ct[i], tat[i], wt[i]);
    }

    printf("Average Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
}

void memory_virtualization(void) {
    int pageSize, numPages;
    int frame[50];

    printf("\nMemory Virtualization (Paging)\n");
    printf("Enter page size: ");
    scanf("%d", &pageSize);
    printf("Enter number of pages: ");
    scanf("%d", &numPages);

    if (pageSize <= 0 || numPages <= 0 || numPages > 50) {
        printf("Invalid paging values.\n");
        return;
    }

    printf("Enter frame number for each page:\n");
    for (int i = 0; i < numPages; i++) {
        printf("Page %d -> Frame: ", i);
        scanf("%d", &frame[i]);
    }

    while (1) {
        int la;
        printf("Enter logical address (-1 to stop): ");
        scanf("%d", &la);
        if (la < 0) {
            break;
        }

        int page = la / pageSize;
        int offset = la % pageSize;
        if (page < 0 || page >= numPages) {
            printf("Invalid logical address.\n");
            continue;
        }

        int pa = frame[page] * pageSize + offset;
        printf("Physical address: %d\n", pa);
    }
}

int main(void) {
    cpu_virtualization();
    memory_virtualization();
    return 0;
}
