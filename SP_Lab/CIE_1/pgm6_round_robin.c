#include <stdio.h>

#define MAX_P 20

int main(void) {
    int n, tq;
    int bt[MAX_P], rt[MAX_P], ct[MAX_P], wt[MAX_P], tat[MAX_P];

    printf("Round Robin Scheduling\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_P) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);
    if (tq <= 0) {
        printf("Time quantum must be positive.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Burst time of P%d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    // Simple RR version: all processes arrive at time 0
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
        tat[i] = ct[i];          // AT = 0, so TAT = CT
        wt[i] = tat[i] - bt[i];  // WT = TAT - BT
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d\t%d\t%d\t%d\t%d\n", i + 1, bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
