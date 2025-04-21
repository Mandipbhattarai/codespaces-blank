#include <iostream>
#include <fstream>
using namespace std;

int main(int argc,char* argv[]){
    if(argc!=3){
        cout<<"Invalid number of args"<<endl;
        return 1;
    }
    string source = argv[1];
    string keyword = argv[2];
    source+=".txt";
    string line;

    ifstream files(source);
    if(!files){
        cout<<"Error opening the file for searching"<<endl;
        return 1;
    }

    bool isFound = false;
    int lineNumber=1;
    while(getline(files,line)){
        int pos = 0;
        while((pos = line.find(keyword,pos))!=string::npos){
            cout<<"Keyword "<<keyword<<" found at line Number "<<lineNumber<<endl;
            pos+=keyword.length();
            isFound = true;
        }
        lineNumber++;
    }
    files.close();
    
    if(!isFound){
        cout<<"Could not find the keyword"<<endl;
        return 1;
    }

    cout<<"Completed the file search"<<endl;
    return 0;
}