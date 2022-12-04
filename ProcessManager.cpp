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
    if(*processName == ""){
        command = LIST_ALL_PROCESS_COMMAND;
    }else{
        command = FIND_PROCESS_BY_NAME_COMMAND + *processName + REDIRECT_TO_FILE_COMMAND;
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
    while(getline(file, dataLine)){
        column = 0;
        data.clear();
        while (column < 10) {
            while(dataLine.at(0) == space[0]){
                dataLine.erase(0, 1);
            }
            index = dataLine.find(space);
            data.push_back(dataLine.substr(0, index));
            dataLine.erase(0, index + 1);
            column++;
        }
        processList.push_back(data);
    }

    file.close();
    return processList;
}

