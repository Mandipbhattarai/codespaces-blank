#include <queue>
#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <climits>
using namespace std;

void calculateTurnaroundTime(int n, vector<int>& completionTime, vector<int>& arrivalTime, vector<int>& turnAroundTime) {
    for (int i = 0; i < n; i++) {
        turnAroundTime[i] = completionTime[i] - arrivalTime[i];
    }
}

void calculateWaitingTime(int n, vector<int>& turnAroundTime, vector<int>& burstTime, vector<int>& waitTime) {
    for (int i = 0; i < n; i++) {
        waitTime[i] = turnAroundTime[i] - burstTime[i];
    }
}

void printResults(int n, vector<int>& process, vector<int>& arrivalTime, vector<int>& burstTime, 
    vector<int>& completionTime, vector<int>& turnAroundTime, vector<int>& waitTime, 
    vector<int>& gantt) {
cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT" << endl;
for (int i = 0; i < n; i++) {
cout << process[i] << "\t" << arrivalTime[i] << "\t" << burstTime[i] << "\t"
<< completionTime[i] << "\t" << turnAroundTime[i] << "\t" << waitTime[i] << endl;
}

cout << "\nGantt Chart:\n";
cout << " ";
for (int i = 0; i < gantt.size(); i++) {
cout << "----";
}
cout << "\n|";

for (int i = 0; i < gantt.size(); i++) {
cout << " P" << gantt[i] << " |";
}

cout << "\n ";
for (int i = 0; i < gantt.size(); i++) {
cout << "----";
}

cout << "\n0";
int time = 0;
for (int i = 0; i < gantt.size(); i++) {
time += burstTime[gantt[i] - 1]; 
cout << "   " << time;
}
cout << endl;
}


void fcfs(int n, vector<int>& process, vector<int>& arrivalTime, vector<int>& burstTime) {
    vector<int> completionTime(n), turnAroundTime(n), waitTime(n);
    vector<int> gantt;
    int totalTurnAroundTime = 0, totalWaitTime = 0;

    completionTime[0] = arrivalTime[0] + burstTime[0];
    gantt.push_back(process[0]);

    for (int i = 1; i < n; i++) {
        int startTime = max(completionTime[i - 1], arrivalTime[i]);
        completionTime[i] = startTime + burstTime[i];
        gantt.push_back(process[i]);
    }

    calculateTurnaroundTime(n, completionTime, arrivalTime, turnAroundTime);
    calculateWaitingTime(n, turnAroundTime, burstTime, waitTime);

    for (int i = 0; i < n; i++) {
        totalTurnAroundTime += turnAroundTime[i];
        totalWaitTime += waitTime[i];
    }

    printResults(n, process, arrivalTime, burstTime, completionTime, turnAroundTime, waitTime, gantt);

    cout << "\nAverage Turnaround Time: " << (float)totalTurnAroundTime / n << endl;
    cout << "Average Waiting Time: " << (float)totalWaitTime / n << endl;
}



void sjfNonPreemptive(int n, vector<int>& process, vector<int>& arrivalTime, vector<int>& burstTime) {
    vector<int> completionTime(n), turnAroundTime(n), waitTime(n);
    vector<int> gantt;
    int totalTurnAroundTime = 0, totalWaitTime = 0;
    vector<bool> visited(n, false);
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int minBurst = INT_MAX, minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && arrivalTime[i] <= currentTime && burstTime[i] < minBurst) {
                minBurst = burstTime[i];
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            currentTime++;
        } else {
            visited[minIndex] = true;
            currentTime += burstTime[minIndex];
            completionTime[minIndex] = currentTime;
            turnAroundTime[minIndex] = completionTime[minIndex] - arrivalTime[minIndex];
            waitTime[minIndex] = turnAroundTime[minIndex] - burstTime[minIndex];

            gantt.push_back(process[minIndex]);
            totalTurnAroundTime += turnAroundTime[minIndex];
            totalWaitTime += waitTime[minIndex];
            completed++;
        }
    }

    printResults(n, process, arrivalTime, burstTime, completionTime, turnAroundTime, waitTime, gantt);

    cout << "\nAverage Turnaround Time: " << (float)totalTurnAroundTime / n << endl;
    cout << "Average Waiting Time: " << (float)totalWaitTime / n << endl;
}

void sjfPreemptive(int n, vector<int>& process, vector<int>& arrivalTime, vector<int>& burstTime) {
    vector<int> remainingTime(n), completionTime(n), turnAroundTime(n), waitTime(n);
    vector<int> gantt;
    int totalTurnAroundTime = 0, totalWaitTime = 0;
    int completed = 0, currentTime = 0;
    vector<bool> visited(n, false);

    for (int i = 0; i < n; i++) remainingTime[i] = burstTime[i];

    while (completed < n) {
        int minBurst = INT_MAX, minIndex = -1;
        for (int i = 0; i < n; i++) {
            if (arrivalTime[i] <= currentTime && remainingTime[i] > 0 && remainingTime[i] < minBurst) {
                minBurst = remainingTime[i];
                minIndex = i;
            }
        }

        if (minIndex == -1) {
            currentTime++;
        } else {
            remainingTime[minIndex]--;
            currentTime++;

            gantt.push_back(process[minIndex]);

            if (remainingTime[minIndex] == 0) {
                completed++;
                completionTime[minIndex] = currentTime;
                turnAroundTime[minIndex] = completionTime[minIndex] - arrivalTime[minIndex];
                waitTime[minIndex] = turnAroundTime[minIndex] - burstTime[minIndex];

                totalTurnAroundTime += turnAroundTime[minIndex];
                totalWaitTime += waitTime[minIndex];
            }
        }
    }

    printResults(n, process, arrivalTime, burstTime, completionTime, turnAroundTime, waitTime, gantt);

    cout << "\nAverage Turnaround Time: " << (float)totalTurnAroundTime / n << endl;
    cout << "Average Waiting Time: " << (float)totalWaitTime / n << endl;
}

void roundRobin(int n, vector<int>& process, vector<int>& arrivalTime, vector<int>& burstTime, int timeQuantum) {
    vector<int> remainingTime(n), completionTime(n, -1), turnAroundTime(n), waitTime(n);
    vector<int> gantt;
    int totalTurnAroundTime = 0, totalWaitTime = 0;
    queue<int> readyQueue;
    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        remainingTime[i] = burstTime[i];
    }

    int index = 0;
    while (completed < n) {
        while (index < n && arrivalTime[index] <= time) {
            readyQueue.push(index);
            index++;
        }

        if (!readyQueue.empty()) {
            int idx = readyQueue.front();
            readyQueue.pop();
            gantt.push_back(process[idx]);

            int executionTime = min(timeQuantum, remainingTime[idx]);
            time += executionTime;
            remainingTime[idx] -= executionTime;

            while (index < n && arrivalTime[index] <= time) {
                readyQueue.push(index);
                index++;
            }

            if (remainingTime[idx] == 0) {
                completionTime[idx] = time;
                turnAroundTime[idx] = completionTime[idx] - arrivalTime[idx];
                waitTime[idx] = turnAroundTime[idx] - burstTime[idx];

                totalTurnAroundTime += turnAroundTime[idx];
                totalWaitTime += waitTime[idx];
                completed++;
            } else {
                readyQueue.push(idx);
            }
        } else {
            time = arrivalTime[index]; 
        }
    }

    printResults(n, process, arrivalTime, burstTime, completionTime, turnAroundTime, waitTime, gantt);

    cout << "\nAverage Turnaround Time: " << (float)totalTurnAroundTime / n << endl;
    cout << "Average Waiting Time: " << (float)totalWaitTime / n << endl;
}

void priorityNonPreemptive(int n, vector<int>& process, vector<int>& arrivalTime, vector<int>& burstTime, vector<int>& priority) {
    vector<pair<int, int>> order;
    for (int i = 0; i < n; i++) {
        order.push_back({priority[i], i});
    }

    sort(order.begin(), order.end());

    vector<int> completionTime(n), turnAroundTime(n), waitTime(n);
    vector<int> gantt;
    int totalTurnAroundTime = 0, totalWaitTime = 0;
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        int idx = order[i].second;

        if (arrivalTime[idx] > currentTime) {
            currentTime = arrivalTime[idx];
        }

        currentTime += burstTime[idx];
        completionTime[idx] = currentTime;
        turnAroundTime[idx] = completionTime[idx] - arrivalTime[idx];
        waitTime[idx] = turnAroundTime[idx] - burstTime[idx];

        gantt.push_back(process[idx]);

        totalTurnAroundTime += turnAroundTime[idx];
        totalWaitTime += waitTime[idx];
    }

    printResults(n, process, arrivalTime, burstTime, completionTime, turnAroundTime, waitTime, gantt);

    cout << "\nAverage Turnaround Time: " << (float)totalTurnAroundTime / n << endl;
    cout << "Average Waiting Time: " << (float)totalWaitTime / n << endl;
}

void priorityPreemptive(int n, vector<int>& process, vector<int>& arrivalTime, vector<int>& burstTime, vector<int>& priority) {
    vector<int> remainingTime(burstTime.begin(), burstTime.end());
    vector<int> completionTime(n, -1), turnAroundTime(n), waitTime(n);
    vector<int> gantt;
    int totalTurnAroundTime = 0, totalWaitTime = 0;
    int completed = 0, currentTime = 0;

    vector<int> indices(n);
    iota(indices.begin(), indices.end(), 0);
    sort(indices.begin(), indices.end(), [&](int a, int b) {
        return arrivalTime[a] < arrivalTime[b];
    });

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int nextProcess = 0;

    while (completed < n) {
        while (nextProcess < n && arrivalTime[indices[nextProcess]] <= currentTime) {
            int idx = indices[nextProcess];
            pq.push({priority[idx], idx});
            nextProcess++;
        }

        if (!pq.empty()) {
            int currentPriority = pq.top().first;
            int idx = pq.top().second;
            pq.pop();

            remainingTime[idx]--;
            currentTime++;

            gantt.push_back(process[idx]);

            if (remainingTime[idx] == 0) {
                completionTime[idx] = currentTime;
                turnAroundTime[idx] = completionTime[idx] - arrivalTime[idx];
                waitTime[idx] = turnAroundTime[idx] - burstTime[idx];
                totalTurnAroundTime += turnAroundTime[idx];
                totalWaitTime += waitTime[idx];
                completed++;
            } else {
                pq.push({currentPriority, idx}); 
            }
        } else {
            if (nextProcess < n) {
                currentTime = arrivalTime[indices[nextProcess]];
            } else {
                currentTime++; 
            }
        }
    }

    printResults(n, process, arrivalTime, burstTime, completionTime, turnAroundTime, waitTime, gantt);

    cout << "\nAverage Turnaround Time: " << (float)totalTurnAroundTime / n << endl;
    cout << "Average Waiting Time: " << (float)totalWaitTime / n << endl;
}

int main() {
    int choice, n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<int> process(n), arrivalTime(n), burstTime(n), priority(n);

    cout << "Enter the processes: \n";
    for (int i = 0; i < n; i++) {
        cin >> process[i];
    }

    cout << "Enter the arrival time for the respective processes: \n";
    for (int i = 0; i < n; i++) {
        cin >> arrivalTime[i];
    }

    cout << "Enter the burst time for the respective processes: \n";
    for (int i = 0; i < n; i++) {
        cin >> burstTime[i];
    }

    do {
        cout << "\nChoose a scheduling algorithm:";
        cout << "\n1. First Come First Serve (FCFS)";
        cout << "\n2. Non-Preemptive Shortest Job First (SJF)";
        cout << "\n3. Preemptive Shortest Job First (SJF)";
        cout << "\n4. Round Robin";
        cout << "\n5. Priority Non-Preemptive";
        cout << "\n6. Priority Preemptive";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                fcfs(n, process, arrivalTime, burstTime);
                break;
            case 2:
                sjfNonPreemptive(n, process, arrivalTime, burstTime);
                break;
            case 3:
                sjfPreemptive(n, process, arrivalTime, burstTime);
                break;
            case 4:
                int timeQuantum;
                cout << "Enter time quantum: ";
                cin >> timeQuantum;
                roundRobin(n, process, arrivalTime, burstTime, timeQuantum);
                break;
            case 5:
                cout << "Enter the priority for the respective processes: \n";
                for (int i = 0; i < n; i++) {
                    cin >> priority[i];
                }
                priorityNonPreemptive(n, process, arrivalTime, burstTime, priority);
                break;
            case 6:
                cout << "Enter the priority for the respective processes: \n";
                for (int i = 0; i < n; i++) {
                    cin >> priority[i];
                }
                priorityPreemptive(n, process, arrivalTime, burstTime, priority);
                break;
            case 7:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}
