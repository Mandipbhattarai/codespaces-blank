#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h> // mandatory
#include <cstdlib>
#include <unistd.h>
using namespace std;

void keywordAnalyzer(char* source,char* destination, char* keyword){
    int pipefd[2]; // 0-> read 1-> write
    pid_t cpid1, cpid2;
    
    if(!pipe(pipefd)){
        cout<<"Error creating the pipe!"<<endl;
        exit(EXIT_FAILURE);
    }

    cpid1 = fork();
    if(cpid1<0){
        cout<<"Error creating the child process 1"<<endl;
        exit(EXIT_FAILURE);
    }
    else if(cpid1 == 0){
        cout<<"The child process is "<<getpid()<<" and the parent process is "<<getppid()<<endl;

        close(pipefd[0]);

        int inputfd = open(source, O_RDONLY);

        if(!inputfd){
            cout<<"Error opening the file"<<endl;
            exit(EXIT_FAILURE);
        }

        dup2(inputfd,STDIN_FILENO);
        dup2(pipefd[1],STDOUT_FILENO);

        close(inputfd);
        close(pipefd[1]);

        execlp("cat","cat",(char*)NULL);
        cerr<<"Error in the file"<<endl;
        exit(EXIT_FAILURE);
    }
    cpid2 = fork();

    if(cpid2<0){
        cout<<"Error creating the child process 2"<<endl;
        exit(EXIT_FAILURE);
    }
    else if(cpid2==0){
        cout<<"Running the child process 2"<<endl;
        close(pipefd[1]);
        int outfd = open(destination, O_CREAT | O_TRUNC | O_WRONLY,0644);

        if(!outfd){
            cerr<<"Error creating the second file descriptor"<<endl;
            exit(EXIT_FAILURE);
        }

        dup2(pipefd[0],STDIN_FILENO);
        dup2(outfd,STDOUT_FILENO);

        close(pipefd[0]);
        close(outfd);

        execlp("grep","grep","-i",keyword,(char*)NULL);
        cerr<<"Error in searching"<<endl;
        exit(EXIT_FAILURE);
    }

    cout<<"File searched successfully!"<<endl;

}


int main(int argc,char* argv[]){
    if(argc!=4){
        cout<<"Invalid Number of ARGS"<<endl;
        return 1;
    }
    // ./ass3 source destination keyword
    cout<<"Parent PID is: "<<getpid()<<endl;

    keywordAnalyzer(argv[1],argv[2],argv[3]);


    return 0;
}