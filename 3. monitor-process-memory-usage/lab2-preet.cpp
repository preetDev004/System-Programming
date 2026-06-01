#include <iostream>
#include <vector>
#include "pidUtil.h"

int main(){
    std::vector<int> pidList;

    // 1. Get a list of all pids & print their names
    ErrStatus err = GetAllPids(pidList);
    if (err != Err_OK) {
        std::cerr << "Error getting pids: " << GetErrorMsg(err) << std::endl;
        return 1;
    }

    for (int pid: pidList) {
        std::string pName;
        err = GetNameByPid(pid, pName);
        if (err != Err_OK) {
            std::cerr << "Error getting name for pid " << pid << ": " << GetErrorMsg(err) << std::endl;
            continue;
        }
        std::cout << "PID: " << pid << ", Name: " << pName << std::endl;
    }

    // 2. Set PID to 1 and get its name
    int pid = 1;
    std::string pName;
    err = GetNameByPid(pid, pName);
    if (err != Err_OK) {
        std::cerr << "Error getting name for pid " << pid << ": " << GetErrorMsg(err) << std::endl;
        return 1;
    }
    std::cout << "PID: " << pid << ", Name: " << pName << std::endl;

    // 3. Get a PID by name "Lab2"
    std::string pNameExist= "Lab2";
    err = GetPidByName(pNameExist, pid);
    if (err != Err_OK) {
        std::cerr << "Error getting pid for name " << pNameExist << ": " << GetErrorMsg(err) << std::endl;
        return 1;
    }
    std::cout << "Name: " << pNameExist << ", PID: " << pid << std::endl;

    // 4. Get a PID by name "Lab11"
    std::string pNameErr = "Lab11";
    err = GetPidByName(pNameErr, pid);
    if (err != Err_OK) {
        std::cerr << "Error getting pid for name " << pNameErr << ": " << GetErrorMsg(err) << std::endl;
        return 1;
    }
    std::cout << "Name: " << pNameErr << ", PID: " << pid << std::endl;

    return 0;
}
