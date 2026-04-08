#include <stdio.h>

#define MAX_P 20

int main(void) {
    int n;
    int at[MAX_P], bt[MAX_P], rt[MAX_P], ct[MAX_P], tat[MAX_P], wt[MAX_P];
    int completed = 0, currentTime = 0;

    printf("Preemptive SJF (SRTF) Scheduling\n");
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
        rt[i] = bt[i];
        ct[i] = tat[i] = wt[i] = 0;
    }

    while (completed < n) {
        int shortest = -1;

        // Pick arrived process with minimum remaining time
        for (int i = 0; i < n; i++) {
            if (at[i] <= currentTime && rt[i] > 0) {
                if (shortest == -1 || rt[i] < rt[shortest]) {
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            // CPU idle if no process has arrived yet
            currentTime++;
            continue;
        }

        // Execute selected process for 1 time unit (preemptive behavior)
        rt[shortest]--;
        currentTime++;

        if (rt[shortest] == 0) {
            completed++;
            ct[shortest] = currentTime;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
        }
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
