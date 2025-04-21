#include <iostream>
#include <bits/stdc++.h>
using namespace std;


void calculateTurnAround(int n, vector<int>completionTime, vector<int> arrivalTime, vector<int>&turnAroundTIme){
    for(int i=0;i<n;i++){
        turnAroundTIme[i] = completionTime[i] - arrivalTime[i];
    }
}

void calculateWaitTime(int n, vector<int>turnAroundTIme, vector<int> burstTime, vector<int>&waitTime){
    for(int i=0;i<n;i++){
        waitTime[i] = turnAroundTIme[i] - burstTime[i];
    }
}


void fcfs(int n,vector<int>process,vector<int> arrivalTime,vector<int>burstTime){
    vector<int> completionTime(n), waitTime(n), turnAroundTime(n);
    int totalTurnAroundTime=0,totalWaitTime = 0;
    vector<int>gantt;

    completionTime[0] = burstTime[0] + arrivalTime[0];
    gantt.push_back(process[0]);
    for(int i=1;i<n;i++){
        int startTime = max(completionTime[i-1],arrivalTime[i]);
        completionTime[i] = burstTime[i] + startTime;
        gantt.push_back(process[i]);
    }

    calculateTurnAround(n,completionTime,arrivalTime,turnAroundTime);
    calculateWaitTime(n,turnAroundTime,burstTime,waitTime);

    for(int i=0;i<n;i++){
        totalTurnAroundTime+=turnAroundTime[i];
        totalWaitTime+=waitTime[i];
    }

    cout<<"Average Turn Around Time: "<<(float)totalTurnAroundTime /n<<endl;
    cout<<"Average Wait Time: "<<(float)totalWaitTime /n<<endl;

    cout<<endl;
    cout<<"Gantt Chart is: "<<endl;
    for(int i=0;i<gantt.size();i++){
        cout<<gantt[i]<<" ";
    }
    cout<<endl<<"-------------------------------";
}

void sjfNonPreemptive(int n,vector<int>process,vector<int>arrivalTime,vector<int>burstTime){
    vector<int> completionTime(n), turnAroundTime(n),waitTime(n);
    int tturnA =0 ,twaitt = 0;
    vector<int> gantt;
    vector<int> visited(n,false);
    int currentTime = 0, completed =0;

    while(completed<n){
        int minBurst = INT_MAX, minIndex = -1;
        for(int i=0;i<n;i++){
            if(!visited[i] && arrivalTime[i]<=currentTime && burstTime[i]<minBurst){
                minBurst = burstTime[i];
                minIndex = i;
            }
        }

        if(minIndex == -1 ) currentTime++;
        else {
            visited[minIndex] = true;
            currentTime += burstTime[minIndex];
            completionTime[minIndex] = currentTime;
            turnAroundTime[minIndex] = completionTime[minIndex] - arrivalTime[minIndex];
            waitTime[minIndex] = turnAroundTime[minIndex] - burstTime[minIndex];
            
            gantt.push_back(minIndex);
            tturnA += turnAroundTime[minIndex];
            twaitt+=waitTime[minIndex];
            completed++;
        }



    }

    cout<<"Gantt Chart..."<<endl;
    for(int i:gantt) cout<<i<<" ";
    cout<<endl;

}

void sjfPreemptive(int n,vector<int>process,vector<int>arrivalTime,vector<int>burstTime){
    vector<int> remainingTime(n),turnAroundTime(n), waitTime(n),completionTime(n);
    vector<bool> finished(n,false);
    int currentTime = 0,  completed =0;
    int totalTurnAround = 0, totalWait =0;
    vector<int>gantt;

    for(int i=0;i<n;i++) remainingTime[i] = burstTime[i];


    while(completed<n){
        int minBurst = INT_MAX, minIndex = -1;
        for(int i=0;i<n;i++){
            if(arrivalTime[i]<= currentTime && remainingTime[i]>0 && remainingTime[i] < minBurst){
                minBurst = remainingTime[i];
                minIndex = i;
            }
        }
        if(minIndex == -1) currentTime ++;
        else {
            remainingTime[minIndex]--;
            currentTime++;
            gantt.push_back(minIndex);

            if(remainingTime[minIndex]==0){
                completed++;
                completionTime[minIndex] = currentTime;
                turnAroundTime[minIndex] = completionTime[minIndex] - arrivalTime[minIndex];
                waitTime[minIndex] = turnAroundTime[minIndex] - burstTime[minIndex];

                totalTurnAround+=turnAroundTime[minIndex];
                totalWait+=waitTime[minIndex];
            }

        }

    }
    cout<<"Gantt Chart"<<endl;
    for(int i:gantt) cout<<i<<" ";
    cout<<endl;



}


void roundRobin(int n ,vector<int> process, vector<int>arrivalTime,vector<int>burstTime,int timeQunatum){
    vector<int>gantt;
    vector<int>completionTime(n),turnAroundTime(n),waitTime(n);
    vector<int>remainingTime = burstTime;
    int totalTurnAroundTime = 0, totalWaitTime=0;
    int time =0, index=0, completed = 0;
    queue<int> readyQueue;


    while(completed<n){
        while(index<n && arrivalTime[index]<=time){
            readyQueue.push(index);
            index++;
        }

        if(!readyQueue.empty()){
            int idx = readyQueue.front();
            readyQueue.pop();
            gantt.push_back(process[idx]);

            int executionTime = min(timeQunatum,remainingTime[idx]);
            time+= executionTime;
            remainingTime[idx]-=executionTime;

            while(index<n && arrivalTime[index]<=time){
                readyQueue.push(index);
                index++;
            }
            if(remainingTime[idx] == 0){
                completionTime[idx] = time;
                turnAroundTime[idx] = completionTime[idx] - arrivalTime[idx];
                waitTime[idx] = turnAroundTime[idx] - burstTime[idx];
                completed++;
            }else{
                readyQueue.push(idx);
            }
        }else{
            time = arrivalTime[index];
        }



    }


    cout<<"Gantt Chart"<<endl;
    for(int i:gantt) cout<<i<<" ";
    cout<<endl;
}


void priorityNon(int n ,vector<int> process, vector<int>arrivalTime,vector<int>burstTime,vector<int>priority){
    vector<int> gantt;
    vector<int> completionTime(n), turnAroundTime(n), waitTime(n);
    vector<bool> isDone(n, false);
    int totalTurnAroundTime = 0, totalWaitTime = 0;
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int minPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (!isDone[i] && arrivalTime[i] <= currentTime) {
                if (priority[i] < minPriority || (priority[i] == minPriority && arrivalTime[i] < arrivalTime[idx])) {
                    minPriority = priority[i];
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            currentTime++;
            continue;
        }

        currentTime += burstTime[idx];
        completionTime[idx] = currentTime;
        turnAroundTime[idx] = completionTime[idx] - arrivalTime[idx];
        waitTime[idx] = turnAroundTime[idx] - burstTime[idx];
        gantt.push_back(process[idx]);
        isDone[idx] = true;
        completed++;
        totalTurnAroundTime += turnAroundTime[idx];
        totalWaitTime += waitTime[idx];
    }

    cout << "Gantt Chart:\n";
    for (int i : gantt) {
        cout << "P" << i << " ";
    }
    cout << "\n";

}




int main(){
    vector<int> process = {1,2,3,4};
    vector<int> arrivalTime = {0,0,0,0};
    vector<int> burstTime = {3,5,6,1};
    vector<int> priority = {2,3,4,1};
    sjfPreemptive(process.size(),process,arrivalTime,burstTime);

    int timeQunatum = 2;
    roundRobin(process.size(),process,arrivalTime,burstTime,timeQunatum);
    priorityNon(process.size(),process,arrivalTime,burstTime,priority);

    return 0;
}