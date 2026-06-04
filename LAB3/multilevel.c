#include <stdio.h>

#define MAX 20

int main() {
    int n, i, time = 0, completed = 0;

    int at[MAX], bt[MAX], rt[MAX], ct[MAX], wt[MAX], tat[MAX];
    int type[MAX]; // 0 = system, 1 = user

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("\nProcess %d\n", i);

        printf("Enter arrival time: ");
        scanf("%d", &at[i]);

        printf("Enter burst time: ");
        scanf("%d", &bt[i]);

        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &type[i]);

        rt[i] = bt[i];
    }

    int done[MAX] = {0};

    while(completed < n) {

        int current = -1;

        // Step 1: Check system processes first
        for(i = 0; i < n; i++) {
            if(at[i] <= time && rt[i] > 0 && type[i] == 0) {
                current = i;
                break; // FCFS among system
            }
        }

        // Step 2: If no system process, check user
        if(current == -1) {
            for(i = 0; i < n; i++) {
                if(at[i] <= time && rt[i] > 0 && type[i] == 1) {
                    current = i;
                    break; // FCFS among user
                }
            }
        }

        // Step 3: CPU idle
        if(current == -1) {
            time++;
            continue;
        }

        // Step 4: Execute 1 unit
        rt[current]--;
        time++;

        // Step 5: Completion
        if(rt[current] == 0) {
            ct[current] = time;
            tat[current] = ct[current] - at[current];
            wt[current] = tat[current] - bt[current];

            completed++;
        }
    }

    float avg_wt = 0, avg_tat = 0;

    printf("\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");

    for(i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
            i,
            (type[i] == 0) ? "System" : "User",
            at[i], bt[i], ct[i], wt[i], tat[i]);

        avg_wt += wt[i];
        avg_tat += tat[i];
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat/n);

    return 0;
}
