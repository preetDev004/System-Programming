#ifndef UTILS_H
#define UTILS_H

#include <string>

class ProcessInfo {
public:
    std::string name;
    int pid;
    std::string state;
    long vmSize;
    long vmRSS;

    ProcessInfo();
};

bool isProcessDir(const std::string &dirName);
bool getProcessStatus(const std::string &pidDir, ProcessInfo &process);

#endif
