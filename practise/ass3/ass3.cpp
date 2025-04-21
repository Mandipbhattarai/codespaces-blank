#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

void keywordAnalyzer(const char* source,const char* destination, const char* keyword){
    int pipefd[2];
    pid_t cpid1,cpid2;

    if(pipe(pipefd)==-1){
        cerr<<"Error: Opening file";
        exit(EXIT_FAILURE);
    }

    cpid1 = fork();
    if(cpid1==-1){
        cerr<<"Error: Opening file";
        exit(EXIT_FAILURE);
    }
    if(cpid1 == 0){
        close(pipefd[0]);
        int logFd = open(source,O_RDONLY);

        if(logFd == -1){
            cerr<<"Error: Opening file";
            exit(EXIT_FAILURE);
        }

       dup2(logFd,STDIN_FILENO);
       dup2(pipefd[1],STDOUT_FILENO);

       close(pipefd[1]);
       close(logFd);

        execlp("cat","cat",(char*)NULL);
    }

    cpid2 = fork();
    if(cpid2==-1){
        cerr<<"Error: Opening file";
        exit(EXIT_FAILURE);
    }

    if(cpid2 ==0){
        close(pipefd[1]);
        dup2(pipefd[0],STDIN_FILENO);

        int outfd = open(destination,O_CREAT | O_TRUNC | O_WRONLY , 0644);
        if(outfd == -1){
            cerr<<"Error: Opening file";
            exit(EXIT_FAILURE);
        }
        dup2 (outfd, STDOUT_FILENO);
        close(pipefd[0]);
        close(outfd);
        execlp("grep","grep","-i",keyword,(char*)NULL);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(cpid1,NULL,0);
    waitpid(cpid2,NULL,0);

}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <inputFile> <outputFile> <keyword>" << endl;
        return 1;
    }
    cout << "Parent PID: " << getpid() << endl;
    keywordAnalyzer(argv[1], argv[2], argv[3]);

    return 0;
}
