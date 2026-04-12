#include <stdio.h>

#define INF 9999

struct Process {
    int pid, arrival_time, burst_time, remaining_time, priority;
    int waiting_time, turnaround_time;
};

// Pick arrived process with highest priority (lowest value) that still needs CPU time.
int select_process(struct Process p[], int n, int current_time) {
    int idx = -1;
    int best_priority = INF;

    for (int i = 0; i < n; i++) {
        if (p[i].arrival_time <= current_time && p[i].remaining_time > 0) {
            if (p[i].priority < best_priority) {
                best_priority = p[i].priority;
                idx = i;
            }
        }
    }
    return idx;
}

int main() {
    int n, time = 0, completed = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter AT, BT, and Priority for P%d: ", p[i].pid);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
        p[i].remaining_time = p[i].burst_time;
    }

    printf("\nExecution Order: ");
    while (completed < n) {
        int idx = select_process(p, n, time);

        if (idx != -1) {
            // Run selected process for 1 time unit (preemption point).
            printf("P%d ", p[idx].pid);
            p[idx].remaining_time--;
            time++; 

            if (p[idx].remaining_time == 0) {
                completed++;
                p[idx].turnaround_time = time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            }
        } else {
            // CPU is idle when no process has arrived.
            time++;
        }
    }

    // Final result table.
    printf("\n\nPID\tAT\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].priority, p[i].waiting_time, p[i].turnaround_time);
    }

    return 0;
}