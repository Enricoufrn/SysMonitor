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

#define LIST_ALL_PROCESS_COMMAND "ps fo pid,cpuid,user,pri,ni,state,%cpu,%mem,time,command -A"
#define FILTER_PROCESS " | grep "
#define REDIRECT_TO_FILE_COMMAND " > processList.txt"
#define TEMP_FILE_NAME "processList.txt"
#define REMOVE_TEMP_FILE "rm processList.txt"
#define SET_CPU_COMMAND "taskset -pc "

using namespace std;

class ProcessManager{
private:
    string* processName;
public:
    ProcessManager();
    ~ProcessManager();
    vector<vector<string>> getAllProcess();
    void killProcess(int pid);
    void stop(int pid);
    void continueProcess(int pid);
    void setCpu(string pid, string cpu);
    void setPriority(int pid, int priority);
    void setName(string newProcessName);
};

#endif // PROCESSMANAGER_H
