// Write a C program to simulate Real-Time CPU Scheduling
// algorithms:
// a) Rate- Monotonic
// b) Earliest-deadline First
// c) Proportional scheduling

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rateMonotonicScheduling(int processes[], int burstTime[], int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (burstTime[j] > burstTime[j + 1])
            {
                // Swap burst times
                int temp = burstTime[j];
                burstTime[j] = burstTime[j + 1];
                burstTime[j + 1] = temp;

                // Swap corresponding processes
                int tempProcess = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = tempProcess;
            }
        }
    }

    printf("Rate-Monotonic Scheduling Order:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d with Burst Time %d\n", processes[i], burstTime[i]);
    }
}

void earliestDeadlineFirstScheduling(int processes[], int burstTime[], int deadlines[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (deadlines[j] > deadlines[j + 1])
            {

                int tempDeadline = deadlines[j];
                deadlines[j] = deadlines[j + 1];
                deadlines[j + 1] = tempDeadline;

                // Swap corresponding processes
                int tempProcess = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = tempProcess;

                // Swap corresponding burst times
                int tempBurstTime = burstTime[j];
                burstTime[j] = burstTime[j + 1];
                burstTime[j + 1] = tempBurstTime;
            }
        }
    }

    printf("Earliest-Deadline First Scheduling Order:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d with Burst Time %d and Deadline %d\n", processes[i], burstTime[i], deadlines[i]);
    }
}
void proportionalScheduling(int processes[], int burstTime[], int n)
{
    int totalBurstTime = 0;
    for (int i = 0; i < n; i++)
    {
        totalBurstTime += burstTime[i];
    }

    printf("Proportional Scheduling Order:\n");
    for (int i = 0; i < n; i++)
    {
        float proportion = (float)burstTime[i] / totalBurstTime;
        printf("Process %d with Burst Time %d and Proportion %.2f\n", processes[i], burstTime[i], proportion);
    }
}

int main()
{

    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processes[n];
    int burstTime[n];
    int deadlines[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter process ID, burst time and deadline for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i], &burstTime[i], &deadlines[i]);
    }

    rateMonotonicScheduling(processes, burstTime, n);
    earliestDeadlineFirstScheduling(processes, burstTime, deadlines, n);
    proportionalScheduling(processes, burstTime, n);

    return 0;
}
