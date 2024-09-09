#include "../include/ToDoList.h"
#include "../include/IOFunctions.h"
#include "../include/Log.h"

#include <fstream> // For creating files

ToDoList::ToDoList() {
    initializeClass();
}

void ToDoList::initializeClass() {
    // Loads tasks from the file if they exist, otherwise they will be created

    std::string m_ExecutablePath = getExecutablePath();
    m_IniFilePath = m_ExecutablePath + "config.ini";
    m_TextFilePath = m_ExecutablePath + "list.txt";

    bool doesIniFileExist = doesDirectoryExist(m_IniFilePath);

    if (doesIniFileExist) {
        setTextFilePath(getLastUsedTextFilePathFromFile(m_IniFilePath));
        setTaskList(importTasksFromFile(m_TextFilePath));
    }
    else {
        createFile(m_IniFilePath);
        createFile(m_TextFilePath);
        saveCurrentTextFilePathToIniFile(m_ExecutablePath + "config.ini", m_ExecutablePath + "list.txt");
    }
}

void ToDoList::addToVectorList() {
    // Adds tasks to the vector via validated inputs from the user

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string task;

    while (true) {
        Log("\nEnter your to-do task (or enter 'Q' to go back): ");
        std::getline(std::cin, task);

        if (task == "Q" || task == "q") {
            break;
        }
        else if (isInputValidated(task) == false) {
            errorLog("Cannot leave empty space at the start or at the end.\n");
        }
        else {
            m_taskList.push_back(task);
        }
        Log('\n');
    }
}

void ToDoList::deleteFromVectorList() {
    // Deletes selected task in the vector by the user

    // So the user can choose
    showTheVectorList();

    while (!(m_taskList.empty())) {
        Log("\nEnter the task number you wish to delete (or enter 'Q' to go back): ");
        std::string userChoice;
        std::cin >> userChoice;

        if (userChoice == "Q" || userChoice == "q") {
            break;
        }

        try {
            size_t indexDel = std::stoi(userChoice) - 1;
            if (indexDel < m_taskList.size()) {
                m_taskList.erase(m_taskList.begin() + indexDel);
                successLog("Successfully deleted a task, updated list:\n");
                showTheVectorList();
            }
            else {
                errorLog("Enter a valid task number.\n");
            }
        }
        catch (const std::exception&) {
            errorLog("Enter a number.\n");
        }
    }
    Log('\n');
}

void ToDoList::emptyVectorList() {
    m_taskList.clear();
}

void ToDoList::showTheVectorList() {
    // Shows saved contents from the vector to the screen

    Log('\n');

    if (m_taskList.empty()) {
        Log("Your to-do list is empty.\n\n");
        return;
    }

    Log("Here's your to-do list:\n");

    short int taskNum = 1;
    for (const std::string& TASK : m_taskList) {
        std::cout << '\t' << taskNum << ". " + TASK << '\n';
        taskNum++;
    }
    Log('\n');
}

void ToDoList::saveToFile() {
    // Saves tasks from the vector to the saved file path

    std::ofstream fileWriter(m_TextFilePath);

    if (fileWriter.is_open()) {
        successLog("\nFile opened successfully, writing to file...\n");

        for (const std::string& TASK : m_taskList) {
            fileWriter << TASK << '\n';
        }
        fileWriter.close();
        successLog("File has been saved.\n\n");
    }
    else {
        errorLog("Unable to open the file.\n");
    }
}

void ToDoList::setTextFilePath(std::string x) {
    m_TextFilePath = x;
}

std::string ToDoList::getTextFilePath() {
    return m_TextFilePath;
}

std::string ToDoList::getIniFilePath() {
    return m_IniFilePath;
}

void ToDoList::setTaskList(std::vector<std::string> x) {
    m_taskList = x;
}

std::vector<std::string> ToDoList::getTaskList() {
    return m_taskList;
}