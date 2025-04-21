#include <iostream>
#include <fstream>
using namespace std;

int main(int argc,char* argv[]){
    if(argc!=3){
        cout<<"Invalid number of args"<<endl;
        return 1;
    }
    string source = argv[1];
    string destination = argv[2];
    source+=".txt";
    destination+=".txt";
    string line;

    ifstream inputfile(source);
    if(!inputfile){
        cout<<"Error opening the input file"<<endl;
        return 1;
    }

    ofstream outputfile(destination);
    if(!outputfile){
        cout<<"Error opening the output file"<<endl;
        return 1;
    }

    while(getline(inputfile,line)){
        outputfile<<line<<'\n';
    }

    cout<<"Copied the contents from one file to next!"<<endl;

    return 0;
}