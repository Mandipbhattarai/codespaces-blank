#include <bits/stdc++.h>
using namespace std;

int fcfs(vector<int>&req,int head,int seekTime){ // done
    int total = 0,curr=head;
    cout<<"FCFS. Head at "<<curr;
    for(int r:req){
        cout<<" -> "<<r;
        total+=abs(r-curr);
        curr = r;
    }
    cout<<endl;
    total *= seekTime;
    cout<<"Total is "<<total<<endl;
    return total;
}

int sstf(vector<int>&req,int head,int seekTime){
    vector<bool>visited(req.size(),false);
    int curr=head,total=0;

    cout<<"SSTF: Current Head at: "<<curr;
    for(int i=0;i<req.size();i++){
        int minDist = INT_MAX,index =-1;
        for(int j=0;j<req.size();j++){
            if(!visited[j] && abs(req[j]-curr)<minDist){
                minDist = abs(req[j]-curr);
                index = j;
            }
        }
        visited[index] = true;
        cout<<" -> "<<req[index];
        total+=abs(req[index]-curr);
        curr= req[index];
    }
    cout<<endl;
    total*=seekTime;
    cout<<"Total is "<<total;
    return total;
}


int scan(vector<int> &req,int head,int seekTime,int discSize){
    req.push_back(head);
    req.push_back(0);
    req.push_back(discSize-1);
    sort(req.begin(),req.end());

    int curr = head, total =0;
    int idx = find(req.begin(),req.end(),head) - req.begin();
    cout<<endl;
    cout<<"SCAN. Head at "<<curr;
    for(size_t i = idx + 1;i<req.size();i++){
        cout<<" -> "<<req[i];
        total += abs(req[i]-curr);
        curr = req[i];
    }
    for(int i=idx-1; i>=0;i--){
        cout<<" -> "<<req[i];
        total+= abs(req[i]-curr);
        curr = req[i];
    }

    total*= seekTime;
    cout<<"Total "<<total;

    return total;
}


int cscan(vector<int> req, int head, int seekTime, int disk) {
    req.push_back(head);
    req.push_back(0);
    req.push_back(disk-1);
    sort(req.begin(),req.end());

    int curr = head, total = 0;
    int idx = find(req.begin(),req.end(),head) - req.begin();
    cout<<"CSCAN. Head at "<<curr;
    for(size_t i = idx+1;i<req.size();i++){
        cout<<" -> "<< req[i];
        total+= abs(req[i]-curr);
        curr = req[i];
    }

    if(curr!=disk-1){
        total+=abs(curr-(disk-1));
        curr = 0;
        cout<<" -> "<<curr;
    }

    for(size_t i=0;i<idx;i++){
        cout<<" -> "<<req[i];
        total+=abs(req[i]-curr);
        curr = req[i];
    }


    int totalTime = total * seekTime;
    cout << "\nTotal Seek Time (C-SCAN): " << totalTime << " ms\n";
    return totalTime;
}


int main(){
    int discsize = 100;
    vector<int>req = {42,41,57,44,17,77,90};
    int seekTime = 1;
    int head = 65;
    fcfs(req,head,seekTime);
    cout<<endl;
    sstf(req,head,seekTime);

    cout<<endl;
    cscan(req,head,seekTime,discsize);

}