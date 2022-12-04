#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <vector>

#define LIST_ALL_PROCESS_COMMAND "ps fo pid,cpuid,user,pri,ni,state,%cpu,%mem,time,command -A > processList.txt"
#define FIND_PROCESS_BY_NAME_COMMAND "ps fo pid,cpuid,user,pri,ni,state,%cpu,%mem,time,command -C "
#define REDIRECT_TO_FILE_COMMAND "> processList.txt"
#define TEMP_FILE_NAME "processList.txt"
#define REMOVE_TEMP_FILE "rm processList.txt"

using namespace std;

class ProcessManager{
private:
    string* processName;
public:
    ProcessManager();
    ~ProcessManager();
    vector<vector<string>> getAllProcess();
    void kill(int pid);
    void stop(int pid);
    void continueProcess(int pid);
    void setCpu();
    void setPriority(int pid, int priority);
    void setName(string newProcessName);
};

#endif // PROCESSMANAGER_H
