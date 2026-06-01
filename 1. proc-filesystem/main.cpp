#include <iostream>
#include <vector>
#include <algorithm>
#include <dirent.h>

#include "utils.h"

void printTopRSSProcesses(std::vector<ProcessInfo> &processes) {
    std::sort(
        processes.begin(),
        processes.end(),
        [](const ProcessInfo &a,
           const ProcessInfo &b) {

            return a.vmRSS > b.vmRSS;
        }
    );

    std::cout
        << "\n===== Top 5 Processes "
        << "(VmRSS > 10MB) =====\n\n";

    int limit =std::min(5, (int)processes.size());

    for (int i = 0; i < limit; i++) {
        const ProcessInfo &p = processes[i];

        std::cout
            << i + 1 << ". "
            << p.name
            << " | PID: " << p.pid
            << " | VmRSS: "
            << p.vmRSS
            << " KB\n";
    }
}

int main() {
    DIR *proc = opendir("/proc");

    if (proc == nullptr) {
        perror("Unable to open /proc");
        return 1;
    }

    struct dirent *entry;
    std::vector<ProcessInfo> highMemoryProcesses;

    std::cout
        << "===== All Accessible Processes =====\n\n";

    while ((entry = readdir(proc)) != nullptr) {
        std::string dirName = entry->d_name;

        // Skip non-process directories
        if (!isProcessDir(dirName)) {
            continue;
        }

        ProcessInfo process;

        // Read process information
        if (!getProcessStatus(dirName, process)) {
            // Skip inaccessible processes
            continue;
        }

        std::cout
            << "PID: " << process.pid
            << " | State:" << process.state
            << " | VmSize: "
            << process.vmSize << " KB"
            << " | VmRSS: "
            << process.vmRSS << " KB\n";

        // Filter processes using > 10 MB RSS
        if (process.vmRSS > 10240) {
            highMemoryProcesses.push_back(process);
        }
    }

    closedir(proc);
    printTopRSSProcesses(highMemoryProcesses);

    return 0;
}
