#include <stdio.h>

#define MAX_P 20
#define INF 9999

int main(void) {
    int n;
    int at[MAX_P], bt[MAX_P], ct[MAX_P], tat[MAX_P], wt[MAX_P];
    int done[MAX_P] = {0};
    int completed = 0, time = 0;

    printf("Non-Preemptive SJF Scheduling\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_P) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("\nProcess P%d\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &at[i]);
        printf("Burst time: ");
        scanf("%d", &bt[i]);
        ct[i] = tat[i] = wt[i] = 0;
    }

    while (completed < n) {
        int idx = -1;
        int minBT = INF;

        for (int i = 0; i < n; i++) {
            if (!done[i] && at[i] <= time && bt[i] < minBT) {
                minBT = bt[i];
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += bt[idx];
        ct[idx] = time;
        tat[idx] = ct[idx] - at[idx];
        wt[idx] = tat[idx] - bt[idx];
        done[idx] = 1;
        completed++;
    }

    double totalWT = 0, totalTAT = 0;
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
