#include "../include/ToDoList.h"
#include "../include/IOFunctions.h"
#include "../include/Log.h"

#include <fstream>

ToDoList::ToDoList() {
    setTextFilePath(getLastUsedTextFilePath());
    setTaskList(importTasksFromFile(m_TextFilePath));
}

void ToDoList::showMenu() {
    Log("==========\n");
    Log("To-Do List\n");
    Log("==========\n\n");
    Log("Select an option:\n");
    Log("\t1. Add to-do task\n");
    Log("\t2. Show to-do list\n");
    Log("\t3. Delete from to-do list\n");
    Log("\t4. Save the list to file\n");
    Log("\t5. Open/create text file\n");
    Log("\t6. Quit the program\n\n");
}

void ToDoList::addToVectorList() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string task;

    while (true) {
        Log("\nEnter your to-do task (or enter 'Q' to go back): ");
        std::getline(std::cin, task);

        if (task.empty() || std::isspace(task.front()) || std::isspace(task.back())) {
            errorLog("Cannot leave empty space at the start or at the end.\n");
        }
        else if (task == "Q" || task == "q") {
            break;
        }
        else {
            m_taskList.push_back(task);
        }
        Log('\n');
    }
}

void ToDoList::deleteFromVectorList() {
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

void ToDoList::showTheVectorList() {
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

void ToDoList::setTaskList(std::vector<std::string> x) {
    m_taskList = x;
}

std::vector<std::string> ToDoList::getTaskList() {
    return m_taskList;
}