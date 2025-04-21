#include <iostream>
#include <fstream>
using namespace std;

int main(int argc,char*argv[]){
    if(argc!=3){
        cout<<"Invalid Number of args";
        return 1;
    }

    string file = argv[1];
    string keyword = argv[2];

    file +=".txt";
    string line;

    bool found = false;
    ifstream files(file);
    if(!files){
        cout<<"Error opening the file";
        return 1;
    }

    int lineNumber = 1;
    while(getline(files,line)){
        size_t pos = 0;
        while(pos = line.find(keyword,pos)!=string::npos){
            cout<<"Keyword: "<<keyword<<"found in line number: "<<lineNumber<<endl;
            pos+=keyword.length();
            found=true;
        }
        lineNumber++;
    }
    files.close();
    if(!found){
        cout<<"Could not find the keyword"<<endl;
    }
    return 0;
}