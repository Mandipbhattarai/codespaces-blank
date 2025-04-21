#include <bits/stdc++.h>
using namespace std;

void fcfs(vector<int>pages,int frames){
    vector<int>frameSpace(frames,-1);
    int framePointer = 0;
    int faults = 0;

    for(int i=0;i<pages.size();i++){
        bool pageFound = false;
        int page = pages[i];
        for(int j=0;j<frames;j++){
            if(frameSpace[j] ==page){
                pageFound= true;
                break;
            }
        }

        if(pageFound){
            cout<<"HIT! ";
        }else{
            faults++;
            if(frameSpace[framePointer]!=-1){
                cout<<"Removing " << frameSpace[framePointer]<<" and replacing with "<< page;
            }
            frameSpace[framePointer] = page;
            framePointer = (framePointer+1) %frames;
        }

        cout<<" Frame : [";
        for (auto p:frameSpace){
            if(p==-1) cout<<" -";
            else cout<<p<<" ";
        }
        if(pageFound) cout<<" ]"<<endl;
        else cout<<" ]*" <<endl;
    }
    cout<<"Page faults "<<faults<<endl;;
}

void lru(vector<int>pages,int frames){
    vector<int> pageFrame(frames,-1);
    vector<int> lastUsed(frames,-1);
    int faults = 0;

    cout<<"Sequence is: "<<endl;
    for(int i:pages){
        cout<<i<<" ";
    }

    for(int i=0;i<pages.size();i++){
        int page = pages[i];
        bool pageFound = false;
        int framePointer = -1;

        for(int j=0;j<frames;j++){
            if(pageFrame[j]==page){
                pageFound=true;
                framePointer = j;
                break;
            }
        }

        if(pageFound){
            lastUsed[framePointer] = i;
            cout<<"Page HIT! ";
        }else{
            faults++;
            int lruIndex =0;
            for(int j=1;j<frames;j++){
                if(lastUsed[j]<lastUsed[lruIndex])
                    lruIndex=j;
            }
            if (pageFrame[lruIndex] != -1) {
                cout << "Removing " << pageFrame[lruIndex] << ", ";
            }
            pageFrame[lruIndex] = page;
            lastUsed[lruIndex] = i;
            cout<<"Inserted"<<" ";
        }
        cout << " | Frames: [ ";
        for (int p : pageFrame) {
            if (p != -1) cout << p << " ";
            else cout << "- ";
        }
        if(!pageFound){
            cout << "] *\n";
        }else{
            cout << "]\n";
        }
    }

    cout << "\nTotal Page Faults: " << faults << endl;

}

void optimal(vector<int> pages,int frames){
    vector<int> frameSpace(frames,-1);
    int faults =0;

    cout<<"Seq"<<endl;
    for(int p:pages){
        cout<<p<<" ";
    }
    cout<<endl;


    for(int i=0;i<pages.size();i++){
        int page = pages[i];
        bool isFound = false;

        for(int j=0;j<frames;j++){
            if(frameSpace[j]==page){
                isFound = true;
                break;
            }
        }

        if(isFound){
            cout<<"Page HIT! ";
        }else{
            faults++;
            
            int emptyFrame = -1;
            for(int j=0;j<frames;j++){
                if(frameSpace[j]==-1){
                    emptyFrame = j;
                    break;
                }
            }
            
            if(emptyFrame!=-1){
                frameSpace[emptyFrame] = page;
                cout<<"Inserted Page"<<endl;
            }else{
                vector<int> nextuse(frames,INT_MAX);
                for(int j=0;j<frames;j++){
                    for(int k=i+1;k<pages.size();k++){
                        if(pages[k]==frameSpace[j]){
                            nextuse[j] = k;
                            break;
                        }
                    }
                }
                int optimalIndex=0;
                for(int j=1;j<frames;j++){
                    if(nextuse[j]>nextuse[optimalIndex]){
                        optimalIndex = j;
                    }
                }
                cout << "Removing " << frameSpace[optimalIndex] << ", ";
                frameSpace[optimalIndex] = page; // Replace with new page
                cout << "Inserted " << page;
            }

        }
        cout << "\nTotal Page Faults: " << faults << endl;


    }

}




int main(){
    vector<int> pages = {1,2,3,4,5,1,2,1,5};
    int frames = 2;
    optimal(pages,frames);
    return 0;
}