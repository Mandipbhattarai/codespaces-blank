#include <iostream>
#include <fstream>
using namespace std;

int main(int argc,char* argv[]){
    if(argc!=3){
        cout<<"use 3 args"<<endl;
        return 1;
    }

    string firstFile = argv[1];
    string secondFile = argv[2];

    firstFile+=".txt";
    secondFile+=".txt";

    string line;

    ifstream oldfile(firstFile);
    if(!oldfile){
        cout<<"Could not open the old file"<<endl;
        return 1;
    }

    ofstream newFile(secondFile);
    if(!newFile){
        cout<<"Couldnot open the newFile"<<endl;
        return 1;
    }

    while(getline(oldfile,line)){
        newFile<<line<<endl;
    }

    cout<<"Finished copying the file"<<endl;

    oldfile.close();
    newFile.close();


    return 0;
}