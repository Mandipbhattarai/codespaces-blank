#include <bits/stdc++.h>
using namespace std;

void displayBlockState(vector<int>blocks,vector<int>tempBlock){
    cout<<"Current Memory Block State: "<<endl;
    cout<< left << setw(15)<<"Block No."<<setw(15) << "Total Size"<< setw(15)<<"Available Space" <<setw(15)<<"Used Space"<<endl;
    cout<< string(60,'-') <<endl;
    for(int i=0;i<blocks.size();i++){
        cout<< left <<setw(15)<<i+1 << setw(15)<<blocks[i]<<setw(15)<<tempBlock[i]<<setw(15)<<blocks[i]-tempBlock[i]<<endl;
    }
    cout<<endl;
}

void firstFit(vector<int>blocks,vector<int>process){
    int blockSize = blocks.size();
    int processSize = process.size(); 
    vector<int> tempBlocks(blockSize);
    vector<int> allocated(processSize,-1);
    for(int i=0;i<blockSize;i++){
        tempBlocks[i] = blocks[i];
    }

    for(int i=0;i<processSize;i++){
        for(int j=0;j<blockSize;j++){
            if(tempBlocks[j]>=process[i]){
                allocated[i] = j;
                tempBlocks[j] -= process[i];
                break;
            }
        }
    }

    displayBlockState(blocks,tempBlocks);
    
}


void worstFit(vector<int>blocks,vector<int>process){
    int blockSize = blocks.size();
    int processSize = process.size();
    vector<int> allocated(processSize,-1);
    vector<int> tempBlocks(blockSize);
    for(int i=0;i<blockSize;i++){
        tempBlocks[i] = blocks[i];
    }
    
    cout<<"Starting Allocation: "<<endl;
    for(int i=0;i<processSize;i++){
        int index = -1;
        for(int j=0;j<blockSize;j++){
            if(process[i]<=tempBlocks[j]){
                if(index==-1 ||  tempBlocks[index] < tempBlocks[j]){
                    index = j;
                }
            }
        }    
        if(index == -1){
            cout<<"Could not allocate"<<endl;
        }else{
            allocated[i] =index; 
            tempBlocks[index] -= process[i];
            cout << "Process " << i + 1 << " of size " << process[i]
            << " allocated to Block " << index << endl;
}
        
    }

    displayBlockState(blocks,tempBlocks);

}


void bestFit(vector<int>blocks,vector<int>process){
    int blockSize = blocks.size();
    int processSize = process.size();
    vector<int> tempBlocks(blockSize);
    vector<int> allocated(processSize,-1);

    for(int i=0;i<blockSize;i++){
        tempBlocks[i] = blocks[i];
    }

    // for(int i=0;i<processSize;i++){
    //     int index=-1;
    //     for(int j=0;j<blockSize;j++){
    //        if(tempBlocks[j]>=process[i]){
    //         if(index == -1 || tempBlocks[j]<tempBlocks[index]){
    //             index = j;
    //         }
    //        }
    //     }
    //     if(index==-1){
    //         cout<<"Could not allocate";
    //     }else{
    //         tempBlocks[index] -= process[i];
    //         allocated[i] = index;
    //     }
    // }
    // displayBlockState(blocks,tempBlocks);


    for(int i=0;i<processSize;i++){
        int index=-1;
        for(int j=0;j<blockSize;j++){
            if(process[i]<=tempBlocks[j]){
                if(index==-1 || tempBlocks[index] > tempBlocks[j]){
                    index = j;
                }
            }
        }
        if(index == -1 ){
            cout<<"Could not allocate"<<endl;
        }else{
            tempBlocks[index] -=process[i];
            allocated[i] = index;
        }
    }
    displayBlockState(blocks,tempBlocks);
}

void nextFit(vector<int>blocks,vector<int>process){
    int processSize = process.size();
    int blockSize = blocks.size();
    vector<int> allocated(processSize,-1);
    vector<int> tempBlocks = blocks;

    int lastAllocated = 0;

    for(int i=0;i<processSize;i++){
        bool isAllocated = false;
        int j = lastAllocated;

        do{
            if(process[i]<=tempBlocks[j]){
                tempBlocks[j]-=process[i];
                isAllocated = true;
                lastAllocated = (j+1) % blockSize;
                break;
            }
            j=(j+1) % blockSize;
        }while(j!=lastAllocated);
        if(!isAllocated){
            cout<<"Could not allocate"<<endl;
        }

    }


    displayBlockState(blocks,tempBlocks);

}



int main(){
    vector<int> blocks = {25,45,25,60,50};
    vector<int> process = {35,25};
    nextFit(blocks,process);

    return 0;
}