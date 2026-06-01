#include "utils.h"

#include <fstream>
#include <sstream>
#include <cctype>

ProcessInfo::ProcessInfo() {
    name = "";
    pid = 0;
    state = "";
    vmSize = 0;
    vmRSS = 0;
}

bool isProcessDir(const std::string &dirName) {
    // Empty directory name
    if (dirName.empty()) {
        return false;
    }

    // Check all characters are digits
    for (char c : dirName) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

bool getProcessStatus(const std::string &pidDir, ProcessInfo &process) {
    std::string path = "/proc/" + pidDir + "/status";

    std::ifstream file(path);

    // Process may terminate or access denied
    if (!file.is_open()) {
        return false;
    }

    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);

        std::string key;
        iss >> key;

        if (key == "Name:") {
            iss >> process.name;
        } else if (key == "Pid:") {
            iss >> process.pid;
        } else if (key == "State:") {
            std::getline(iss, process.state);
        } else if (key == "VmSize:") {
            iss >> process.vmSize;
        } else if (key == "VmRSS:") {
            iss >> process.vmRSS;
        }
    }

    file.close();
    return true;
}
