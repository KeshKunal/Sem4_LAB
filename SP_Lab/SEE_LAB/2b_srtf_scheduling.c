/*
==================================================
QUICK OVERVIEW
==================================================

Purpose:
- Implement Preemptive SJF (SRTF) CPU scheduling algorithm.
- Simulate process scheduling by selecting process with minimum remaining time.

Approach:
1. Read number of processes with their arrival time and burst time.
2. Simulate time step by step (incremental time simulation).
3. At each time step, find the process with minimum remaining time that has arrived.
4. If no process is ready, skip to next time unit.
5. Execute one unit of the selected process and decrement its remaining time.
6. When a process completes, record its completion time.
7. Calculate and display CT, TAT, WT and their averages.

Key Variables:
- pid[] -> process ID
- at[] -> arrival time of each process
- bt[] -> burst time (total CPU time) of each process
- rt[] -> remaining time for each process (updated during simulation)
- ct[] -> completion time of each process
- tat[] -> turnaround time (CT - AT)
- wt[] -> waiting time (TAT - BT)

Algorithm Used:
- Preemptive SJF (Shortest Remaining Time First - SRTF)
  At each time unit, CPU is assigned to the process with minimum remaining time among ready processes.

Time Complexity: O(n²) - for each time unit, we scan all processes to find minimum remaining time

==================================================
*/

 
#include <stdio.h> 
int main() { 
    int n, i, time = 0, min, pos, completed = 0; 
    printf("Enter number of processes: "); 
    scanf("%d", &n); 
    int pid[n], at[n], bt[n], rt[n], ct[n], tat[n], wt[n]; 
    float avgwt = 0, avgtat = 0; 
    for(i = 0; i < n; i++) { 
        pid[i] = i + 1; 
        printf("\nEnter Arrival Time for P%d: ", pid[i]); 
        scanf("%d", &at[i]); 
        printf("Enter Burst Time for P%d: ", pid[i]); 
        scanf("%d", &bt[i]); 
        rt[i] = bt[i]; 
    } 
    while(completed < n) { 
        min = 9999; 
        pos = -1; 
        for(i = 0; i < n; i++) { 
            if(at[i] <= time && rt[i] > 0 && rt[i] < min) { 
                min = rt[i]; 
                pos = i; 
            } 
        } 
        if(pos == -1) { 
            time++; 

        } 
        else { 
            rt[pos]--; 
            time++; 
            if(rt[pos] == 0) { 
                ct[pos] = time; 
                completed++; 
            } 
        } 
    } 
    for(i = 0; i < n; i++) { 
        tat[i] = ct[i] - at[i]; 
        wt[i] = tat[i] - bt[i]; 
        avgwt += wt[i]; 
        avgtat += tat[i]; 
    } 
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n"); 
    for(i = 0; i < n; i++) { 
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", 
        pid[i], at[i], bt[i], ct[i], tat[i], wt[i]); 
    } 
    printf("\nAverage Waiting Time = %.2f", avgwt/n); 
    printf("\nAverage Turnaround Time = %.2f\n", avgtat/n); 
 
    return 0; 
}