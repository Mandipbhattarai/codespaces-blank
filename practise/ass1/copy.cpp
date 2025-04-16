#include <fstream>
#include <bits/stdc++.h>
using namespace std;


int main(int argc,char*argv[]){
    if(argc!=3){
        cout<<"Invalid Number of args";
        return 1;
    }

    int line;
    string inFile = argv[1];
    string outFile = argv[2];

    inFile = inFile + ".txt";
    outFile = outFile + ".txt";

    ifstream oldFile(inFile);
    if(!oldFile){
        return 1;
    }

    ofstream newFile(outFile);
    if(!newFile){
        return 2;
    }

    while(getline(oldFile,line)){
        newFile << line << " ";
    }

    cout<<"File copied successfully";
    newFile.close();
    oldFile.close();
    return 0;

}