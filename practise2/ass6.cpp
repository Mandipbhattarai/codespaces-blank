#include <bits/stdc++.h>
#include <iomanip>
using namespace std;


void displayProcess(vector<int> blocks, vector<int> tempBlocks){
    cout << "Block allocation is given as : " << endl;
    cout << left 
         << setw(15) << "Block No" 
         << setw(15) << "Total Size" 
         << setw(15) << "Allocated" 
         << setw(15) << "Remaining Size" 
         << endl;

    for(int i = 0; i < blocks.size(); i++){
        cout << left 
             << setw(15) << i 
             << setw(15) << blocks[i] 
             << setw(15) << (blocks[i] - tempBlocks[i]) 
             << setw(15) << tempBlocks[i] 
             << endl;
    }
    cout << endl;
}


void firstFit(vector<int>blocks,vector<int>process){
    int processSize = process.size();
    int blockSize = blocks.size();
    vector<int> allocation(processSize,-1);
    vector<int> tempBlock = blocks;

    for(int i=0;i<processSize;i++){
        cout<<"Allocating the process P"<<i<<endl;

        for(int j=0;j<blockSize;j++){
            if(process[i]<= tempBlock[j]){
                allocation[i] = j;
                tempBlock[j] -= process[i];
                break;
            }
        }

        if(allocation[i]==-1){
            cout<<"Could not allocate to process "<<i<<endl;
        }
    }
    displayProcess(blocks,tempBlock);

}

void worstFit(vector<int> blocks,vector<int>process){
    vector<int>allocated(blocks.size(),-1);
    vector<int>tempBlocks = blocks;

    for(int i=0;i<process.size();i++){
        int worstIdx = -1;
        for(int j=0;j<tempBlocks.size();j++){
            if(process[i]<=tempBlocks[j]){
                if(worstIdx == -1 || tempBlocks[j]>tempBlocks[worstIdx]){
                    worstIdx = j;
                }
            }
        }

        if(worstIdx==-1){
            cout<<"Cannot Allocate"<<endl;
        }else{
            allocated[i] = worstIdx;
            tempBlocks[worstIdx] -= process[i];
            cout<<"Allocated the process"<<i<<endl;
        }

    }
    displayProcess(blocks,tempBlocks);


}


void bestFit(vector<int>blocks,vector<int>process){
    vector<int> allocated (blocks.size(),-1);
    vector<int> tempBlocks = blocks;

    for(int i=0;i<process.size();i++){
        int bestIdx = -1;
        for(int j=0;j<tempBlocks.size();j++){
            if(tempBlocks[j]>=process[i]){
                if(bestIdx ==-1 || tempBlocks[j]<tempBlocks[bestIdx] ){
                    bestIdx = j;
                }    
            }
        }
        if(bestIdx == -1){
            cout<<"Could Not Allocate"<<endl;
        }else{
            allocated[i] = bestIdx;
            tempBlocks[bestIdx] -= process[i];
            cout<<"Allocated"<<endl;
        }
    }
    displayProcess(blocks,tempBlocks);
}

void nextFit(vector<int>&blocks,vector<int>&process){
    vector<int>allocated(process.size(),-1);
    vector<int> tempBlocks = blocks;

   int lastAllocated = 0;
   for(int i=0;i<process.size();i++){
        int j = lastAllocated;
        bool isAllocated = false;

        do{
            if(tempBlocks[j]>=process[i]){
                allocated[i] = j;
                tempBlocks[j]-= process[i];
                isAllocated = true;
                lastAllocated = (j + 1) % tempBlocks.size();
            }
            j = (j + 1) % tempBlocks.size();
        }while(j!=lastAllocated);


   }

    displayProcess(blocks,tempBlocks);
}


int main(){
    vector<int> blocks ={14,20,50,40,59};
    vector<int> process = {20,13};
    nextFit(blocks,process);

}
