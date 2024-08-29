#include <iostream>
using namespace std;

// Function to calculate waiting time of each process
void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum) {
    int rem_bt[n]; // Array to store remaining burst time of each process
    for (int i = 0; i < n; i++) rem_bt[i] = bt[i]; // Initialize remaining burst times
    
    int t = 0; // Current time
    while (true) {
        bool done = true; // Flag to indicate if all processes are done
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) { // Check if burst time remains for process i
                done = false; // At least one process is pending
                if (rem_bt[i] > quantum) {
                    t += quantum; // Increase time by quantum
                    rem_bt[i] -= quantum; // Decrease remaining burst time
                } else {
                    t += rem_bt[i]; // Increase time by remaining burst time
                    wt[i] = t - bt[i]; // Calculate waiting time
                    rem_bt[i] = 0; // Process is finished
                }
            }
        }
        if (done) break; // If all processes are done, exit loop
    }
}

// Function to calculate turnaround time of each process
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        // Turnaround time is the sum of burst time and waiting time
        tat[i] = bt[i] + wt[i];
    }
}

// Function to calculate average waiting and turnaround times, and display the results
void findAvgTime(int processes[], int n, int bt[], int quantum) {
    int wt[n], tat[n], total_wt = 0, total_tat = 0;

    // Calculate waiting time and turnaround time for all processes
    findWaitingTime(processes, n, bt, wt, quantum);
    findTurnAroundTime(processes, n, bt, wt, tat);

    cout << "Processes | Burst time | Waiting time | Turn around time\n";
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << " " << i + 1 << "\t\t" << bt[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << endl;
    }

    // Calculate and print average waiting time and average turnaround time
    cout << "Average waiting time = " << (float)total_wt / (float)n << endl;
    cout << "Average turn around time = " << (float)total_tat / (float)n << endl;
}

int main() {
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    int processes[n];
    int bt[n]; // Array to store burst times

    cout << "Enter the burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1; // Assign process ID
        cout << "Process " << i + 1 << ": ";
        cin >> bt[i]; // Input burst time
    }

    cout << "Enter the time quantum: ";
    cin >> quantum; // Input time quantum
    
    // Calculate and display average times
    findAvgTime(processes, n, bt, quantum);
    return 0;
}
