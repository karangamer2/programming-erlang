#include <stdio.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void findWaitingTime(struct Process processes[], int n, int waitingTime[]) {
    int remainingTime[n];
    for (int i = 0; i < n; i++) {
        remainingTime[i] = processes[i].burstTime;
    }

    int complete = 0, t = 0, shortest = 0;
    int minTime = INT_MAX;

    while (complete < n) {
        for (int j = 0; j < n; j++) {
            if (processes[j].arrivalTime <= t && remainingTime[j] < minTime && remainingTime[j] > 0) {
                minTime = remainingTime[j];
                shortest = j;
            }
        }

        remainingTime[shortest]--;
        minTime = remainingTime[shortest];
        if (minTime == 0) {
            complete++;
            processes[shortest].completionTime = t + 1;
            waitingTime[shortest] = processes[shortest].completionTime - processes[shortest].burstTime - processes[shortest].arrivalTime;
            if (waitingTime[shortest] < 0) {
                waitingTime[shortest] = 0;
            }
        }
        t++;
    }
}

void findTurnaroundTime(struct Process processes[], int n, int waitingTime[], int turnaroundTime[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = processes[i].burstTime + waitingTime[i];
    }
}

void findAvgTime(struct Process processes[], int n) {
    int waitingTime[n], turnaroundTime[n];
    findWaitingTime(processes, n, waitingTime);
    findTurnaroundTime(processes, n, waitingTime, turnaroundTime);

    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].id, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].completionTime, waitingTime[i], turnaroundTime[i]);
    }

    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        printf("Enter burst time for Process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
    }

    findAvgTime(processes, n);

    return 0;
}
