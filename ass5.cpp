#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int numProcesses, numResources;
vector<int> available;
vector<vector<int>> maxDemand, allocation, need;
bool systemInitialized = false;

// Function to get valid integer input
void getValidInput(int &value, const string &message) {
    while (true) {
        cout << message;
        if (cin >> value && value >= 0) break;
        cout << "Invalid input! Please enter a non-negative integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Function to get valid vector input
void getValidVector(vector<int> &vec, const string &message) {
    cout << message;
    for (int &val : vec) {
        while (!(cin >> val) || val < 0) {
            cout << "Invalid input! Enter a non-negative integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Function to get valid matrix input
void getValidMatrix(vector<vector<int>> &matrix, const string &message) {
    cout << message;
    for (auto &row : matrix) {
        for (int &val : row) {
            while (!(cin >> val) || val < 0) {
                cout << "(!!Warning!!)Invalid input! Enter a non-negative integer: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}

// Function to calculate need matrix and check for negative values
bool calculateNeedMatrix() {
    need.assign(numProcesses, vector<int>(numResources));
    for (int i = 0; i < numProcesses; i++) {
        for (int j = 0; j < numResources; j++) {
            need[i][j] = maxDemand[i][j] - allocation[i][j];
            if (need[i][j] < 0) {
                cout << "Error: Negative need detected for process P" << i << " and resource " << j << ".\n";
                return false;
            }
        }
    }
    return true;
}

// Function to print the current state
void printState() {
    if (!systemInitialized) {
        cout << "System not initialized. Please initialize first.\n";
        return;
    }
    cout << "\nAvailable Resources:\n";
    for (int i : available) cout << i << " ";
    cout << "\n\nAllocation Matrix:\n";
    for (auto &row : allocation) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }
    cout << "\nNeed Matrix:\n";
    for (auto &row : need) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }
}

// Recursive function to find all safe sequences
void findSafeSequences(vector<int>& work, vector<bool>& finish, vector<int>& safeSeq, vector<vector<int>>& allSeqs) {
    bool found = false;
    for (int p = 0; p < numProcesses; p++) {
        if (!finish[p]) {
            bool canProceed = true;
            for (int j = 0; j < numResources; j++) {
                if (need[p][j] > work[j]) {
                    canProceed = false;
                    break;
                }
            }
            if (canProceed) {
                for (int j = 0; j < numResources; j++) {
                    work[j] += allocation[p][j];
                }
                finish[p] = true;
                safeSeq.push_back(p);
                findSafeSequences(work, finish, safeSeq, allSeqs);
                safeSeq.pop_back();
                finish[p] = false;
                for (int j = 0; j < numResources; j++) {
                    work[j] -= allocation[p][j];
                }
                found = true;
            }
        }
    }
    if (!found) {
        if (safeSeq.size() == numProcesses) {
            allSeqs.push_back(safeSeq);
        }
    }
}

// Function to find and display all safe sequences
void findAllSafeSequences() {
    if (!systemInitialized) {
        cout << "System not initialized. Please initialize first.\n";
        return;
    }
    vector<int> work = available;
    vector<bool> finish(numProcesses, false);
    vector<int> safeSeq;
    vector<vector<int>> allSeqs;
    findSafeSequences(work, finish, safeSeq, allSeqs);

    if (allSeqs.empty()) {
        cout << "No safe sequence found. The system is in an unsafe state.\n";
    } else {
        cout << "All possible safe sequences:\n";
        for (const auto& seq : allSeqs) {
            for (int p : seq) {
                cout << "P" << p << " ";
            }
            cout << "\n";
        }
    }
}

int main() {
    cout << "Enter number of processes and resources: ";
    cin >> numProcesses >> numResources;
    if (numProcesses <= 0 || numResources <= 0) return 0;

    available.resize(numResources);
    maxDemand.assign(numProcesses, vector<int>(numResources));
    allocation.assign(numProcesses, vector<int>(numResources));

    int choice;
    while (true) {
        cout << "\n--- Banker's Algorithm Menu ---\n";
        cout << "1. Initialize system\n";
        cout << "2. Display current state\n";
        cout << "3. Find all safe sequences\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                getValidVector(available, "Enter available resources: ");
                getValidMatrix(maxDemand, "Enter maximum demand matrix:\n");
                getValidMatrix(allocation, "Enter allocation matrix:\n");
                if (!calculateNeedMatrix()) {
                    cout << "Initialization failed due to invalid need values. Terminating program.\n";
                    return 0;
                } else {
                    systemInitialized = true;
                    cout << "System initialized successfully.\n";
                }
                break;
            case 2:
                printState();
                break;
            case 3:
                findAllSafeSequences();
                break;
            case 0:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}