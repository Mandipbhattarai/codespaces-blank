#include <bits/stdc++.h>
using namespace std;

bool isSafe(int resourceNum,int processNum,vector<int> available,vector<vector<int>> allocated,
    vector<vector<int>> maxNeed,vector<vector<int>>need,vector<int>&safeSequence){
        vector<int> work = available;
        vector<int> finished(processNum,false);
        int count =0;

      while(count<processNum){
        bool found = false;
        for(int i=0;i<processNum;i++){
            if(!finished[i]){
                bool canAllocate = true;
                for(int j=0;j<resourceNum;j++){
                    if(work[j]<need[i][j]){
                        canAllocate = false;
                        break;
                    }
                }
                if(canAllocate){
                    for(int j=0;j<resourceNum;j++){
                        work[j]+=allocated[i][j];
                    }
                    found = true;
                    finished[i] = true;
                    safeSequence.push_back(i);
                    count++;
                }
            }
        }
        if(!found){
            cout<<"Could not find"<<endl;
        }

      }

        for(int i: safeSequence){
            cout<<i<<endl;
        }
        return true;
}


int requestResouce(int resourceNum, int processNum, vector<int> available, vector<vector<int>>allocated,
    vector<vector<int>> maxNeed, vector<vector<int>>need, int process, vector<int>request){
        if(process<0 || process> processNum){
            cout<<"Error";
            return 1;
        }

        cout<<"Resource is being requested by: "<<process<<endl;
        for(int r:request) cout<<r<<" ";
        cout<<endl;

        for(int i=0;i<resourceNum;i++){
            if(need[process][i]>request[i]){
                cout<<"Cannot"<<endl;
                return 0;
            }
        }

        for(int i=0;i<resourceNum;i++){
            if(request[i]>available[i]){
                return 1;
            }
        }

        vector<int> savedAvailable = available;
        vector<vector<int>> saveAllocated = allocated;
        vector<vector<int>> savedNeed = need;

        // Allocate the requested resources 
        for(int i=0;i<resourceNum;i++){
            available[i]-=request[i];
            allocated[process][i] += request[i];
            need[process][i]-=request[i];
        }

        vector<int>safeSequence;
        if(isSafe(resourceNum,processNum,available,allocated,maxNeed,need,safeSequence)){
            cout<<"YES"<<endl;
        }else{
            cout<<"Cannot rolling back";
            available = savedAvailable;
            allocated = saveAllocated;
            need = savedNeed;
        }
}



int main(){
    int resourceNum = 3, processNum = 5;

    vector<int> available = {3, 3, 2};  

    vector<vector<int>> allocated = {
        {0, 1, 0},  
        {2, 0, 0},  
        {3, 0, 2},  
        {2, 1, 1},  
        {0, 0, 2}   
    };

    vector<vector<int>> maxNeed = {
        {7, 5, 3},  
        {3, 2, 2},  
        {9, 0, 2},  
        {2, 2, 2},  
        {4, 3, 3}   
    };

    vector<vector<int>> need(processNum,vector <int> (resourceNum));
    for(int i=0;i<processNum;i++){
        for(int j=0;j<resourceNum;j++){
            need[i][j] = maxNeed[i][j] - allocated[i][j];
        }
    }
    vector<int> safeSequence;
    if(isSafe(resourceNum,processNum, available,allocated,maxNeed,need,safeSequence)){
        cout<<"System in safe state!"<<endl;
    }else{
        cout<<"System in unsafe state!"<<endl;
    }
    vector<int> request = {1, 0, 2};  // process 1 requesting
    requestResouce(resourceNum, processNum, available, allocated, maxNeed, need, 1, request);

}