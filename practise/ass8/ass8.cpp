#include <bits/stdc++.h>
using namespace std;

int fifo(const vector<int>& req, int head, int seekTime) {
    int total = 0, curr = head;
    cout << "\nFIFO Order:\nHead at: " << curr;
    for (int r : req) {
        cout << " -> " << r;
        total += abs(r - curr);
        curr = r;
    }
    int totalTime = total * seekTime;
    cout << "\nTotal Seek Time (FIFO): " << totalTime << " ms\n";
    return totalTime;
}

int sstf(vector<int> req, int head, int seekTime) {
    int total = 0, curr = head;
    vector<bool> visited(req.size(), false);
    cout << "\nSSTF Order:\nHead at: " << curr;

    for (size_t i = 0; i < req.size(); ++i) {
        int minDist = INT_MAX, index = -1;
        for (size_t j = 0; j < req.size(); ++j) {
            if (!visited[j] && abs(req[j] - curr) < minDist) {
                minDist = abs(req[j] - curr);
                index = j;
            }
        }
        visited[index] = true;
        cout << " -> " << req[index];
        total += abs(req[index] - curr);
        curr = req[index];
    }

    int totalTime = total * seekTime;
    cout << "\nTotal Seek Time (SSTF): " << totalTime << " ms\n";
    return totalTime;
}

int scan(vector<int> req, int head, int seekTime, int disk) {
    req.push_back(head);        // Add head to request list
    req.push_back(0);
    sort(req.begin(), req.end()); // Sort requests in ascending order

    int total = 0, curr = head;
    int idx = find(req.begin(), req.end(), head) - req.begin(); // Find the current head position

    cout << "\nSCAN Order:\nHead at: " << curr;

    // Move right: Process requests to the right of the head
    for (int i = idx - 1; i >= 0; --i) {
        cout << " -> " << req[i];
        total += abs(req[i] - curr);  // Add the seek time
        curr = req[i];  // Update current position
    }
    for (size_t i = idx + 1; i < req.size(); ++i) {
        cout << " -> " << req[i];
        total += abs(req[i] - curr);  // Add the seek time
        curr = req[i];  // Update current position
    }

    // Move left: Process requests to the left of the head
    // Skip moving to 0 or disk-1 unless it's necessary

    // Calculate total seek time
    int totalTime = total * seekTime;
    cout << "\nTotal Seek Time (SCAN): " << totalTime << " ms\n";
    return totalTime;
}


int cscan(vector<int> req, int head, int seekTime, int disk) {
    req.push_back(head);
    req.push_back(0);
    req.push_back(disk - 1);
    sort(req.begin(), req.end());

    int total = 0, curr = head;
    int idx = find(req.begin(), req.end(), head) - req.begin();

    cout << "\nC-SCAN Order:\nHead at: " << curr;

    // Move right
    for (size_t i = idx + 1; i < req.size(); ++i) {
        cout << " -> " << req[i];
        total += abs(req[i] - curr);
        curr = req[i];
    }

    // Jump to 0 (simulate circular)
    if (curr != disk - 1) {
        total += abs(curr - (disk - 1));
        curr = 0;
        cout << " -> " << curr;
    }

    // Process from start to head
    for (size_t i = 0; i < idx; ++i) {
        cout << " -> " << req[i];
        total += abs(req[i] - curr);
        curr = req[i];
    }

    int totalTime = total * seekTime;
    cout << "\nTotal Seek Time (C-SCAN): " << totalTime << " ms\n";
    return totalTime;
}
int main() {
    int seekTime = 1;
    int disk = 200;
    vector<int> req = {176, 79, 34, 60,
        92, 11, 41, 114};
    int head = 50;

    fifo( req,  head,seekTime);
    cout << endl;

    sstf( req,  head,seekTime);
    cout << endl;

    scan( req,  head,seekTime,disk);
    cout << endl;

    cscan( req,  head,seekTime,disk);
    return 0;
}
