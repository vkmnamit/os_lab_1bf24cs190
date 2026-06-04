#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct {
    int id, bt, deadline, period;
    int ct, wt, tat;
} Process;

void sortEDF(Process p[], int n) {
    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-i-1;j++) {
            if(p[j].deadline > p[j+1].deadline) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

void sortRMS(Process p[], int n) {
    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-i-1;j++) {
            if(p[j].period > p[j+1].period) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

float calculateUtilization(Process p[], int n) {
    float u = 0;
    for(int i=0;i<n;i++) {
        u += (float)p[i].bt / p[i].period;
    }
    return u;
}

void calculateTimes(Process p[], int n) {
    int time = 0;
    for(int i=0;i<n;i++) {
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

void printTable(Process p[], int n, int isEDF) {
    printf("ID\tBF\t");
    if(isEDF) printf("Deadline\t");
    else printf("Period\t\t");
    printf("CT\tWT\tTAT\n");

    for(int i=0;i<n;i++) {
        printf("%d\t%d\t", p[i].id, p[i].bt);
        if(isEDF) printf("%d\t\t", p[i].deadline);
        else printf("%d\t\t", p[i].period);
        printf("%d\t%d\t%d\n", p[i].ct, p[i].wt, p[i].tat);
    }
}

void proportionalScheduling(Process p[], int n) {
    printf("\n===== Proportional Scheduling =====\n");

    float total = 0;
    for(int i=0;i<n;i++) total += p[i].bt;

    printf("ID\tBurst\tShare\n");
    for(int i=0;i<n;i++) {
        float share = p[i].bt / total;
        printf("%d\t%d\t%.2f\n", p[i].id, p[i].bt, share);
    }
}

int main() {
    int n;
    Process p[MAX], temp[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i=0;i<n;i++) {
        p[i].id = i;
        printf("\nProcess %d:\n", i);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Deadline (EDF): ");
        scanf("%d", &p[i].deadline);
        printf("Period (RMS): ");
        scanf("%d", &p[i].period);
    }

    // Copy array for EDF
    for(int i=0;i<n;i++) temp[i] = p[i];

    printf("\n===== Earliest Deadline First (EDF) =====\n");
    sortEDF(temp, n);
    calculateTimes(temp, n);

    float u = calculateUtilization(temp, n);
    printf("CPU Utilization: %.2f\n", u);
    if(u <= 1) printf("Schedulable (Utilization <= 1)\n");

    printTable(temp, n, 1);

    // Copy again for RMS
    for(int i=0;i<n;i++) temp[i] = p[i];

    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");
    sortRMS(temp, n);
    calculateTimes(temp, n);

    float bound = n * (pow(2, (float)1/n) - 1);

    printf("CPU Utilization: %.2f\n", u);
    printf("RM Bound: %.4f\n", bound);

    if(u <= bound) printf("Schedulable (Utilization <= RM Bound)\n");

    printTable(temp, n, 0);

    // Proportional Scheduling
    proportionalScheduling(p, n);

    return 0;
}
