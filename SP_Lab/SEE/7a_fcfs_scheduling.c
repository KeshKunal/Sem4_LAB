#include <stdio.h>

#define MAX_P 20

int main(void) {
    int n;
    int pid[MAX_P], at[MAX_P], bt[MAX_P], ct[MAX_P], tat[MAX_P], wt[MAX_P];

    printf("FCFS CPU Scheduling\n");
    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_P) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nProcess P%d\n", pid[i]);
        printf("Arrival time: ");
        scanf("%d", &at[i]);
        printf("Burst time: ");
        scanf("%d", &bt[i]);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                int t;
                t = at[j]; at[j] = at[j + 1]; at[j + 1] = t;
                t = bt[j]; bt[j] = bt[j + 1]; bt[j + 1] = t;
                t = pid[j]; pid[j] = pid[j + 1]; pid[j + 1] = t;
            }
        }
    }

    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < at[i]) {
            time = at[i];
        }
        ct[i] = time + bt[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        time = ct[i];
    }

    double totalWT = 0, totalTAT = 0;
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
        totalWT += wt[i];
        totalTAT += tat[i];
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
