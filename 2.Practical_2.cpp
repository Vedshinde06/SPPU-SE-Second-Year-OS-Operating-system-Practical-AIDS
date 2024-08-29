#include <iostream>
#include <algorithm> // For sorting the processes based on burst time
using namespace std;

// Structure to represent a process
struct Process {
    int id;         // Process ID
    int burst;      // Burst time
    int wait;       // Waiting time
    int tat;        // Turnaround time
};

// Comparator function to sort processes by burst time
bool compareBurstTime(Process a, Process b) {
    return a.burst < b.burst;
}

// Function to calculate the waiting time for each process
void findWaitingTime(Process processes[], int n) {
    processes[0].wait = 0; // First process has no waiting time
    for (int i = 1; i < n; i++) {
        // Waiting time for current process is the sum of burst times of all previous processes
        processes[i].wait = processes[i - 1].wait + processes[i - 1].burst;
    }
}

// Function to calculate the turnaround time for each process
void findTurnAroundTime(Process processes[], int n) {
    for (int i = 0; i < n; i++) {
        // Turnaround time is the sum of burst time and waiting time
        processes[i].tat = processes[i].burst + processes[i].wait;
    }
}

// Function to calculate average waiting and turnaround times, and display the results
void findAvgTime(Process processes[], int n) {
    // Sort processes by burst time using the compare function
    sort(processes, processes + n, compareBurstTime);

    // Calculate waiting time and turnaround time for all processes
    findWaitingTime(processes, n);
    findTurnAroundTime(processes, n);

    // Initialize total waiting time and total turnaround time for average calculation
    int total_wt = 0, total_tat = 0;

    cout << "Processes | Burst time | Waiting time | Turn around time\n";
    for (int i = 0; i < n; i++) {
        total_wt += processes[i].wait;
        total_tat += processes[i].tat;
        cout << " " << processes[i].id << "\t\t" << processes[i].burst << "\t\t" << processes[i].wait << "\t\t" << processes[i].tat << endl;
    }

    // Calculate and print average waiting time and average turnaround time
    cout << "Average waiting time = " << (float)total_wt / (float)n << endl;
    cout << "Average turn around time = " << (float)total_tat / (float)n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    Process processes[n]; // Array of processes

    cout << "Enter the burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1; // Assign process ID
        cout << "Process " << i + 1 << ": ";
        cin >> processes[i].burst; // Input burst time
    }

    // Calculate and display average times
    findAvgTime(processes, n);
    return 0;
}
