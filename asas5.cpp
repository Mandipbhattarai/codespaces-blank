#include <bits/stdc++.h>
using namespace std;

bool isSafe(int resourceNum,int processNum,vector<int>available,vector<vector<int>>allocated, vector<vector<int>>maxNeed, vector<vector<int>>need,vector<int>&safeSequence)
{
    vector<int>work=available;
    vector<bool>finished(processNum,false);
    int count = 0;

    while(count<processNum){
        bool found = false;
        for(int i=0;i<processNum;i++){
            if(!finished[i]){
                bool canAllocate = true;
                cout<<"Work vector is: "<<endl;
                for(int w:work) cout<<w<<" ";
                cout<<"Need of the process"<<endl;
                for(int n:need[i]) cout<<n<<endl;
                
                for(int j=0;j<resourceNum;j++){
                    if(need[i][j]>work[j]){
                        canAllocate = false;
                        cout<<"need>work"<<endl;
                        break;
                    }
                }      
                if(canAllocate){
                    cout<<"Allocating resource to P"<<i<<endl;
                    for(int j=0;j<resourceNum;j++){
                        work[j]+=allocated[i][j];
                    }
                    found = true;
                    finished[i]= true;
                    safeSequence.push_back(i);
                    count++;

                    cout<<"Updated work vector"<<endl;
                    for(int i:work) cout<<i<<" ";
                    cout<<endl<<"Safe Seq till now: "<<endl;
                    for(int i: safeSequence) cout<<"P"<<i<<" -> ";
                }      
            }
        }
        if(!found){
            cout<<"Couldnot find"<<endl;
            return false;
        }

    }
    cout<<"Safe seq: "<<endl;
    for(int i: safeSequence) cout<<"P"<<i<<"  ";
    return true;

}

bool resourceAllocation(int numResource,int numProcess, vector<int>&available,vector<vector<int>>&allocated, vector<vector<int>>&maxNeed, vector<vector<int>>&need,vector<int>&safeSequence,int process,vector<int>&request){
    if(process<0 || process> numProcess){
        throw out_of_range("Error");
    }
    cout<<"Requesting resource for P"<<process<<endl;
    for(int i:request) cout<<i<<" ";

    for(int i=0;i<numResource;i++){
        if(request[i]>need[process][i]){
            cout<<"Cannot be more than need";
            return false;
        }
    }

    for(int i=0;i<numResource;i++){
        if(request[i]>available[i]){
            cout<<"Cannot allocated more than available";
            return false;
        }
    }

    vector<int> saveAvailable = available;
    vector<vector<int>>saveNeed=need;
    vector<vector<int>>savedAllocated = allocated;

    for(int i=0;i<numResource;i++){
        available[i] -= request[i];
        allocated[process][i] +=request[i];
        need[process][i]-=request[i];
    }


    if(isSafe(numResource,numProcess,saveAvailable,savedAllocated,maxNeed,saveNeed,safeSequence)){
        cout<<"YES"<<endl;
    }else{
        available = saveAvailable;
        allocated = savedAllocated;
        need = saveNeed;
        cout<<"Could not allocate";
        return false;
    }
    return true;
}

void findAllSafeSequences(
    int resourceNum, int processNum,
    vector<int> work,
    vector<vector<int>> allocated,
    vector<vector<int>> need,
    vector<bool> &finished,
    vector<int> &sequence,
    vector<vector<int>> &allSequences
) {
    if (sequence.size() == processNum) {
        allSequences.push_back(sequence);
        return;
    }

    for (int i = 0; i < processNum; i++) {
        if (!finished[i]) {
            bool canAllocate = true;
            for (int j = 0; j < resourceNum; j++) {
                if (need[i][j] > work[j]) {
                    canAllocate = false;
                    break;
                }
            }

            if (canAllocate) {
                // Simulate allocation
                for (int j = 0; j < resourceNum; j++) {
                    work[j] += allocated[i][j];
                }

                finished[i] = true;
                sequence.push_back(i);

                // Recurse
                findAllSafeSequences(resourceNum, processNum, work, allocated, need, finished, sequence, allSequences);

                // Backtrack
                finished[i] = false;
                sequence.pop_back();
                for (int j = 0; j < resourceNum; j++) {
                    work[j] -= allocated[i][j];
                }
            }
        }
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

    vector<vector<int>> need(processNum, vector<int>(resourceNum));
    for(int i = 0; i < processNum; i++){
        for(int j = 0; j < resourceNum; j++){
            need[i][j] = maxNeed[i][j] - allocated[i][j];
        }
    }
    vector<int> safeSequence;
    cout << "Need Matrix:\n";
    for(int i = 0; i < processNum; i++){
        for(int j = 0; j < resourceNum; j++){
            cout << need[i][j] << " ";
        }
        cout << endl;
    }
    vector<int> request = {1, 0, 2};
    int processRequesting = 1;
    bool granted = resourceAllocation(resourceNum, processNum, available, allocated, maxNeed, need, safeSequence, processRequesting, request);
    if(granted){
        cout << "Request granted.\n";
        cout << "New safe sequence:\n";
        for(int i : safeSequence){
            cout << "P" << i << " -> ";
        }
        cout << "Done\n";
    } else {
        cout << "Request denied.\n";
    }
    
    isSafe(resourceNum,processNum,available,allocated,maxNeed,need,safeSequence);
    vector<vector<int>> allSequences;
vector<int> sequence;
vector<bool> finished(processNum, false);
vector<int> work = available;

    findAllSafeSequences(resourceNum, processNum, work, allocated, need, finished, sequence, allSequences);

    // Print all safe sequences
    cout << "\nAll Safe Sequences:\n";
    for (auto seq : allSequences) {
        for (int p : seq)
            cout << "P" << p << " ";
        cout << endl;
    }
    
    return 0;
}
