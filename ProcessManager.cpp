#include "ProcessManager.h"

using namespace std;

ProcessManager::ProcessManager(){
    this->processName = new string;
    *processName = "";
}

ProcessManager::~ProcessManager(){
    ifstream file(TEMP_FILE_NAME);
    if(file.good()){
        system(REMOVE_TEMP_FILE);
    }
}

void ProcessManager::setName(string newProcessName){
    *processName = newProcessName;
}

vector<vector<string>> ProcessManager::getAllProcess(){
    vector<vector<string>> processList;
    string command;
    command = LIST_ALL_PROCESS_COMMAND;
    bool readSecondLine = true;
    if(*processName == ""){
        command.append(REDIRECT_TO_FILE_COMMAND);
    }else{
        readSecondLine = false;
        command.append(FILTER_PROCESS + *processName + REDIRECT_TO_FILE_COMMAND);
    }

    system(command.c_str());

    ifstream file(TEMP_FILE_NAME);
    vector<string> data;
    if(!file.is_open()){
        data.push_back("Error no processo!");
        processList.push_back(data);
    }

    char space[] = " ";
    string dataLine;
    size_t index;
    int column;
    if(readSecondLine)
        getline(file, dataLine);
    while(getline(file, dataLine)){
        column = 0;
        data.clear();
        while (column <= 9) {
            if(column < 9){
                while(dataLine.at(0) == space[0]){
                    dataLine.erase(0, 1);
                }
                index = dataLine.find(space);
            }else{
                index = dataLine.size();
            }
            data.push_back(dataLine.substr(0, index));
            dataLine.erase(0, index + 1);
            column++;
        }
        processList.push_back(data);
    }

    file.close();
    return processList;
}

void ProcessManager::killProcess(int pid){
    kill(pid, SIGKILL);
}
void ProcessManager::stop(int pid){
    kill(pid, SIGSTOP);
}

void ProcessManager::continueProcess(int pid){
    kill(pid, SIGCONT);
}

void ProcessManager::setCpu(string pid, string cpu){
    string command = SET_CPU_COMMAND + cpu + " " + pid;
    system(command.c_str());
}

void ProcessManager::setPriority(int pid, int priority){
    int result = setpriority(PRIO_PROCESS, pid , priority);
    cout << "result = " << result << endl;
}
