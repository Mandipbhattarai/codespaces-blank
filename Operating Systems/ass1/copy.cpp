#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Invalid Number of arguments");
        return 1;
    }
    
    string line;
    string fileextension = ".txt";
    
    string ofile = argv[1];
    string nfile = argv[2];
    
    nfile = nfile + fileextension;
    ofile = ofile + fileextension;

    ifstream oldfile{ofile};
    if(!oldfile){
        printf("Error opening the first file. Please check if it exists");
        return 1;
    }


    ofstream newfile(nfile);

    if(!newfile){
        printf("Error opening the second file. Please check if it exists");
        return 1;
    }

  
    while(getline(oldfile,line)){
        newfile << line <<'\n';
    }
        printf("File has been copied from first to second file successfully! \n");
    oldfile.close();
    newfile.close();


    return 0;
}