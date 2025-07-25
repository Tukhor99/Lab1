#include <stdio.h>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int isCompleted;
};

int main() {
    int n = 5;
    struct Process p[] = {
        {1, 0, 3, 0, 0, 0, 0},
        {2, 1, 2, 0, 0, 0, 0},
        {3, 2, 1, 0, 0, 0, 0},
        {4, 3, 4, 0, 0, 0, 0},
        {5, 0, 2, 0, 0, 0, 0}
    };

    int completed = 0, currentTime = 0;

    while (completed < n) {
        int idx = -1;
        int minBT = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= currentTime && !p[i].isCompleted) {
                if (p[i].burstTime < minBT) {
                    minBT = p[i].burstTime;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            currentTime += p[idx].burstTime;
            p[idx].completionTime = currentTime;
            p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
            p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
            p[idx].isCompleted = 1;
            completed++;
        } else {
            currentTime++; // If no process is available yet
        }
    }

    printf("P\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrivalTime, p[i].burstTime,
               p[i].completionTime, p[i].turnaroundTime, p[i].waitingTime);
    }

    return 0;
}