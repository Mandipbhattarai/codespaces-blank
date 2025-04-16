#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

void copyFile(const char *src, const char *dest) {
    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Failed to create child process for copy." << endl;
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        cout << "Copying file: " << src << " to " << dest << endl;
        execlp("./copy", "copy", src, dest, NULL);
        cerr << "Failed to execute copy program." << endl;
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }
}

void grepFile(const char *file, const char *pattern) {
    pid_t pid = fork();
    if (pid < 0) {
        cerr << "Failed to create child process for grep." << endl;
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        cout << "Searching for pattern: " << pattern << " in file: " << file << endl;
        execlp("./grep", "grep",file, pattern, NULL);
        cerr << "Failed to execute grep program." << endl;
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <source_file> <destination_file> <grep_pattern>" << endl;
        return 1;
    }

    pid_t main_pid = getpid();
    cout << "Main process PID: " << main_pid << endl;

    const char *sourceFile = argv[1];
    const char *destinationFile = argv[2];
    const char *grepPattern = argv[3];

    cout << "Source: " << sourceFile << ".txt, Destination: " << destinationFile << ".txt, Pattern: " << grepPattern << endl;

    copyFile(sourceFile, destinationFile);

    cout<<"------------------------------------------------------------"<<endl;

    grepFile(destinationFile, grepPattern);

    return 0;
}
