#include <bits/stdc++.h>
using namespace std;

// Function to input system data: available resources, max need, allocation, and need matrices
void inputData(int numProcesses, int numResources, vector<int> &available,
               vector<vector<int>> &maxNeed, vector<vector<int>> &allocated, vector<vector<int>> &need) {
    cout << "\nEnter the Available Resources:\n";
    for (int i = 0; i < numResources; i++) {
        cin >> available[i];
        if (available[i] < 0) throw invalid_argument("Available resources cannot be negative.");
    }

    cout << "\nEnter the Maximum Need matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cin >> maxNeed[i][j];
            if (maxNeed[i][j] < 0) throw invalid_argument("Maximum need cannot be negative.");
        }
    }

    cout << "\nEnter the Allocation matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            cin >> allocated[i][j];
            need[i][j] = maxNeed[i][j] - allocated[i][j]; // Calculate need
        }
    }
}

// Function to display the current system state
void displayState(int numProcesses, int numResources, const vector<int> &available,
                  const vector<vector<int>> &maxNeed, const vector<vector<int>> &allocated,
                  const vector<vector<int>> &need) {
    cout << "\nCurrent System State:";

    // Display available resources
    cout << "\nAvailable Resources: ";
    for (int res : available) cout << res << " ";

    // Display maximum need matrix
    cout << "\nMaximum Need Matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "P" << i << ": ";
        for (int val : maxNeed[i]) cout << val << " ";
        cout << endl;
    }

    // Display allocation matrix
    cout << "\nAllocation Matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "P" << i << ": ";
        for (int val : allocated[i]) cout << val << " ";
        cout << endl;
    }

    // Display need matrix
    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < numProcesses; i++) {
        cout << "P" << i << ": ";
        for (int val : need[i]) cout << val << " ";
        cout << endl;
    }
}

// Safety Algorithm to check if the system is in a safe state
bool isSafe(int numProcesses, int numResources, const vector<int> &available,
            const vector<vector<int>> &allocated, const vector<vector<int>> &need, vector<int> &safeSequence) {
    vector<int> work = available;             
    vector<bool> finish(numProcesses, false); 
    int count = 0;                            

    cout << "\nSafety Algorithm Execution:\n";

    while (count < numProcesses) {
        bool found = false;

        for (int i = 0; i < numProcesses; i++) {
            if (!finish[i]) {
                bool canAllocate = true;

                cout << "\n\nChecking Process P" << i << ":\n";
                cout << "Current Work Vector: ";
                for (int w : work) cout << w << " ";
                cout << "\nNeed Vector for P" << i << ": ";
                for (int n : need[i]) cout << n << " ";

                for (int j = 0; j < numResources; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        cout << "\nCannot allocate to P" << i << " as Need > Work for resource " << j;
                        break;
                    }
                }

                if (canAllocate) {
                    cout << "\nAllocating resources to P" << i;
                    for (int j = 0; j < numResources; j++) {
                        work[j] += allocated[i][j];
                    }
                    finish[i] = true;
                    safeSequence.push_back(i);
                    found = true;
                    count++;

                    cout << "\nUpdated Work Vector: ";
                    for (int w : work) cout << w << " ";
                    cout << "\nSafe Sequence so far: ";
                    for (int k : safeSequence) cout << "P" << k << " ";
                }
            }
        }

        if (!found) {
            cout << "\n\nNO SAFE SEQUENCE FOUND - System is in UNSAFE state!";
            return false;
        }
    }

    cout << "\n\nSAFE SEQUENCE FOUND: ";
    for (int i : safeSequence) cout << "P" << i << " ";
    cout << "\nSystem is in SAFE state!";
    return true;
}

// Resource Request Algorithm to handle resource requests
bool requestResources(int numProcesses, int numResources, int process, vector<int> &available,
                      vector<vector<int>> &allocated, vector<vector<int>> &need, vector<int> &request) {
    if (process < 0 || process >= numProcesses) {
        throw out_of_range("Invalid process number.");
    }

    cout << "\nRequesting resources for Process P" << process << ":\n";
    cout << "Requested Vector: ";
    for (int r : request) cout << r << " ";

    // Check if request exceeds the process's maximum need
    for (int i = 0; i < numResources; i++) {
        if (request[i] > need[process][i]) {
            cout << "\nError: Request exceeds maximum need for resource " << i;
            return false;
        }
    }

    // Check if request exceeds the available resources
    for (int i = 0; i < numResources; i++) {
        if (request[i] > available[i]) {
            cout << "\nError: Request exceeds available resources for resource " << i;
            return false;
        }
    }

    // Save current state for potential rollback
    vector<int> savedAvailable = available;
    vector<vector<int>> savedAllocated = allocated;
    vector<vector<int>> savedNeed = need;

    // Allocate requested resources
    for (int i = 0; i < numResources; i++) {
        available[i] -= request[i];
        allocated[process][i] += request[i];
        need[process][i] -= request[i];
    }

    cout << "\n\nAfter Allocation:\n";
    displayState(numProcesses, numResources, available, allocated, allocated, need);

    // Check if the system remains in a safe state
    vector<int> safeSequence;
    if (isSafe(numProcesses, numResources, available, allocated, need, safeSequence)) {
        cout << "\nRequest can be granted immediately!";
        return true;
    } else {
        // Rollback if not safe
        available = savedAvailable;
        allocated = savedAllocated;
        need = savedNeed;
        cout << "\n\nRequest cannot be granted - restoring previous state.";
        return false;
    }
}

// Recursive function to find all safe sequences
void findAllSafeSequences(int numProcesses, int numResources, vector<int> &available,
    vector<vector<int>> &allocated, vector<vector<int>> &need,
    vector<bool> &finish, vector<int> &currentSequence,
    vector<vector<int>> &allSequences) {
    bool found = false;

    for (int i = 0; i < numProcesses; i++) {
        if (!finish[i]) {
            bool canAllocate = true;
            for (int j = 0; j < numResources; j++) {
                if (need[i][j] > available[j]) {
                    canAllocate = false;
                    break;
            }
    }

    if (canAllocate) {
        for (int j = 0; j < numResources; j++) {
            available[j] += allocated[i][j];
        }

        finish[i] = true;
        currentSequence.push_back(i);

        // Recurse
        findAllSafeSequences(numProcesses, numResources, available, allocated, need, finish, currentSequence, allSequences);

        // Backtrack
        for (int j = 0; j < numResources; j++) {
        available[j] -= allocated[i][j];
        }

        finish[i] = false;
        currentSequence.pop_back();
        found = true;
        }   
    }
}

if (!found && currentSequence.size() == numProcesses) {
allSequences.push_back(currentSequence);
}
}
void displayAllSafeSequences(int numProcesses, int numResources, vector<int> available,
    vector<vector<int>> allocated, vector<vector<int>> need) {
    vector<bool> finish(numProcesses, false);
    vector<int> currentSequence;
    vector<vector<int>> allSequences;

    findAllSafeSequences(numProcesses, numResources, available, allocated, need,
    finish, currentSequence, allSequences);

    if (allSequences.empty()) {
        cout << "\nNo safe sequences found. System is in UNSAFE state.\n";
    } else {
        cout << "\nAll Possible Safe Sequences:\n";
    for (const auto &seq : allSequences) {
        for (int pid : seq) {
                cout << "P" << pid << " ";
            }
            cout << "\n";
        }
    }
}

// Menu function to interact with the user
void menu(int numProcesses, int numResources, vector<int> &available, vector<vector<int>> &maxNeed,
          vector<vector<int>> &allocated, vector<vector<int>> &need) {
    int choice;
    do {
        cout << "\nMENU:\n1. Display Current System State\n2. Check System Safety\n3. Request Resources\n4. Show All Safe Sequences\n 5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayState(numProcesses, numResources, available, maxNeed, allocated, need);
                break;
            case 2: {
                vector<int> safeSequence;
                if (isSafe(numProcesses, numResources, available, allocated, need, safeSequence)) {
                    cout << "\nSystem is in SAFE state!";
                } else {
                    cout << "\nSystem is in UNSAFE state!";
                }
                break;
            }
            case 3: {
                int process;
                cout << "Enter process number making the request: ";
                cin >> process;
                if (process < 0 || process >= numProcesses) {
                    throw out_of_range("Invalid process number.");
                }

                vector<int> request(numResources);
                cout << "Enter resource request vector:\n";
                for (int i = 0; i < numResources; i++) {
                    cin >> request[i];
                    if (request[i] < 0) throw invalid_argument("Resource request cannot be negative.");
                }

                requestResources(numProcesses, numResources, process, available, allocated, need, request);
                break;
            }
            case 4:
                displayAllSafeSequences(numProcesses, numResources, available, allocated, need);
                break;

            case 5:
                cout << "\nExiting the program.";
                break;
            default:
                cout << "\nInvalid choice. Please try again.";
        }
    } while (choice != 5);
}

// Main function
int main() {
    try {
        int numProcesses, numResources;
        cout << "Enter number of processes: ";
        cin >> numProcesses;
        if (numProcesses <= 0) {
            throw invalid_argument("Number of processes must be positive.");
        }

        cout << "Enter number of resources: ";
        cin >> numResources;
        if (numResources <= 0) {
            throw invalid_argument("Number of resources must be positive.");
        }

        vector<int> available(numResources);
        vector<vector<int>> maxNeed(numProcesses, vector<int>(numResources));
        vector<vector<int>> allocated(numProcesses, vector<int>(numResources));
        vector<vector<int>> need(numProcesses, vector<int>(numResources));

        inputData(numProcesses, numResources, available, maxNeed, allocated, need);
        for (int i = 0; i < numProcesses; i++) {
            for (int j = 0; j < numResources; j++) {
                if (need[i][j] < 0) {
                    throw runtime_error("Error: Need[" + to_string(i) + "][" + to_string(j) + "] is negative. (Allocation > Max Need)");
                }
            }
        }

        menu(numProcesses, numResources, available, maxNeed, allocated, need);

    } catch (const exception &e) {
        cerr << "\nError: " << e.what();
    }

    return 0;
}
