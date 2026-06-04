#include <stdio.h>

int main() {
    int n, i, time = 0, remain;
    int at[20], bt[20], rem_bt[20];
    int ct[20], tat[20], wt[20], rt[20];
    int tq;

    // For Gantt chart
    int gantt_p[100], gantt_t[100], g = 0;

    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Arrival Time and Burst Time:\n");

    for(i = 0; i < n; i++) {
        printf("P%d AT: ", i+1);
        scanf("%d", &at[i]);

        printf("P%d BT: ", i+1);
        scanf("%d", &bt[i]);

        rem_bt[i] = bt[i];
        rt[i] = -1;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &tq);

    remain = n;

    while(remain > 0) {

        int done = 1;

        for(i = 0; i < n; i++) {

            if(at[i] <= time && rem_bt[i] > 0) {

                done = 0;

                if(rt[i] == -1)
                    rt[i] = time - at[i];

                // Store Gantt chart process
                gantt_p[g] = i;
                gantt_t[g] = time;
                g++;

                if(rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    time += rem_bt[i];
                    rem_bt[i] = 0;

                    ct[i] = time;
                    tat[i] = ct[i] - at[i];
                    wt[i] = tat[i] - bt[i];

                    avg_wt += wt[i];
                    avg_tat += tat[i];
                    avg_rt += rt[i];

                    remain--;
                }
            }
        }

        if(done == 1)
            time++;
    }

    // Last time for Gantt
    gantt_t[g] = time;

    printf("\nGantt Chart:\n");

    for(i = 0; i < g; i++) {
        printf("| P%d ", gantt_p[i]+1);
    }
    printf("|\n");

    for(i = 0; i <= g; i++) {
        printf("%d   ", gantt_t[i]);
    }

    printf("\n\nProcess AT BT CT TAT WT RT\n");

    for(i = 0; i < n; i++) {
        printf("P%d     %d  %d  %d  %d   %d  %d\n",
        i+1, at[i], bt[i], ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);
    printf("\nAverage Response Time = %.2f\n", avg_rt/n);

    return 0;
}
