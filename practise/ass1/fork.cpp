#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;


void copyFile(const char* source,const char* destination){
    pid_t pid = fork();
    if(pid<0){
        cout<<"Failed to create child process: "<<endl;
        exit(EXIT_FAILURE);
    }else if(pid==0){
        cout<<"Child PID: "<<pid;
        cout<<"Copying the file from "<<source<<" to "<<destination<<endl;
        execlp("./copy","copy",source,destination,NULL);
        cerr<<"Failed to execute the file"<<endl;
        exit(EXIT_FAILURE);
    }
    else {
        wait(NULL);  
      }
}

void grepFile(const char* source,const char* keyword){
    pid_t pid  = fork();

    if(pid < 0){
        cout<<"Error creating the child process";
        exit(EXIT_FAILURE);
    }else if(pid==0){
    cout<<"Child PID: "<<pid;

        cout<<"Searching for file: "<<source<<" for keyword: "<<keyword;
        execlp("./grep","grep",source,keyword,NULL);
        cerr<<"Failed to search"<<endl;
        exit(EXIT_FAILURE);
    }else{
        wait(NULL);
    }
}

int main(int argc,char* argv[]){
    if(argc!=4){
        cout<<"Invalid Number of args"<<endl;
        return 1;
    }
    pid_t main_pid = getpid();
    cout<<"Main PID: "<<main_pid<<endl;;


    
    const char *source = argv[1];
    const char* destination = argv[2];
    const char* keyword = argv[3];

    cout<<"Copying the file"<<endl;
    copyFile(source,destination);
    cout<<endl;


    cout<<"Searching in the file"<<endl;
    grepFile(source,keyword);
    cout<<endl;
    return 0;
}