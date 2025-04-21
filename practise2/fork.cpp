#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;

void copyFile(const char* source, const char* destination){
    pid_t pid = fork();
    if(pid < 0 ){
        cout<<"Error creating the fork of the child process "<<endl;
        exit(EXIT_FAILURE);
    }
    else if(pid == 0){
        cout<<"Copying the file whose pid is "<<pid;
        execlp("./copy","copy",source,destination,NULL);
        cerr<<"Error creating the copy in the file"<<endl;
        exit(EXIT_FAILURE);
    }else {
        wait(NULL);
    }
}


void grepFile(const char* source, const char* keyword){
    pid_t pid = fork();
    if(pid < 0){
        cout<<"Error creating the fork of the child process "<<endl;
        exit(EXIT_FAILURE);
    }else if(pid ==  0){
        cout<<"Searching the file and the pid is "<<pid;
        execlp("./grep","grep",source,keyword,NULL);
        cerr<<"Error in searching the file"<<endl;
        exit(EXIT_FAILURE);
    }else{
        wait(NULL);
    }
}

int main(int argc,char* argv[]){
    if(argc!=4){
        cout<<"Invalid number of args"<<endl;
        return 1;
    }
    pid_t main_pid = getpid();
    cout<<"The parent process pid is "<<main_pid<<endl;

    const char* source = argv[1];
    const char* destination = argv[2];
    const char* keyword = argv[3];

    copyFile(source,destination);

    grepFile(source,keyword);



    return 0;
}