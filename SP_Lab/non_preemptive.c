#include <stdio.h>

#define INF 9999

struct Process {
    int pid;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completed;
};

// Returns index of unfinished process with highest priority (lowest value).
int select_highest_priority_process(struct Process p[], int n) {
    int idx = -1;
    int best_priority = INF;

    for (int i = 0; i < n; i++) {
        if (!p[i].completed && p[i].priority < best_priority) {
            best_priority = p[i].priority;
            idx = i;
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
        printf("Enter burst time and priority for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].burst_time, &p[i].priority);
        p[i].completed = 0;
    }

    printf("\nExecution Order: ");
    while (completed < n) {
        int idx = select_highest_priority_process(p, n);

        if (idx != -1) {
            // In non-preemptive scheduling, chosen process runs fully.
            p[idx].waiting_time = time;
            time += p[idx].burst_time;
            p[idx].turnaround_time = time;
            p[idx].completed = 1;
            completed++;
            printf("P%d ", p[idx].pid);
        }
    }

    // Final result table.
    printf("\n\nPID\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t\t%d\t%d\n", 
               p[i].pid, p[i].burst_time, p[i].priority, 
               p[i].waiting_time, p[i].turnaround_time);
    }
    return 0;
}