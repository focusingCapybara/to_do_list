#include "../include/ToDoList.h"
#include "../include/Log.h"
#include "../include/IOFunctions.h"

#include <sstream> // For getline input and converting types
#include <fstream> // For creating files
#include <vector> // For dynamic array
#include <filesystem> // For file directories

void showMenu() {
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

bool isInputValidated(std::string const X) {
    // Returns true if the input has passed the validation, false if it hasn't

    //
    if (X.empty() || std::isspace(X.front()) || std::isspace(X.back())) {
        return false;
    }
    else {
        return true;
    }
}

bool doesDirectoryExist(std::string const PATH) {
    // Returns true or false if the directory exists

    if (std::filesystem::exists(PATH)) {
        return true;
    }
    else {
        return false;
    }
}

void createOrOpenTextFile(ToDoList& todoList) {
    std::string userPath = getUserTextFilePath(todoList);
    userPath = formatPath(userPath);
    todoList.setTextFilePath(userPath);
    createOrOpenFileDecider(todoList);
    saveCurrentTextFilePathToIniFile(todoList.getIniFilePath(), todoList.getTextFilePath());
}

void createFile(std::string const FULL_PATH) {
    // Creates file with given validated path and extension

    std::ofstream fileCreator(FULL_PATH);
    fileCreator.close();

    successLog("File has been created at: ");
    successLog(FULL_PATH);
    std::cout << std::endl << std::endl;
}

void createOrOpenFileDecider(ToDoList& todoList) {
    // Decides whether to create or open the file

    const std::string TEXT_FILE_PATH = todoList.getTextFilePath();
    // Read file
    if (doesDirectoryExist(TEXT_FILE_PATH)) {
        todoList.setTaskList(importTasksFromFile(TEXT_FILE_PATH));
    }
    // Create file
    else {
        createFile(TEXT_FILE_PATH);
        todoList.emptyVectorList();
    }
}

std::vector<std::string> importTasksFromFile(std::string const TEXT_FILE_PATH) {
    // Reads the specified file and saves contents into the vector

    std::ifstream textFileReader(TEXT_FILE_PATH);
    std::vector<std::string> list;

    if (textFileReader.is_open()) {
        successLog("Opened text file at: ");
        successLog(TEXT_FILE_PATH);
        std::cout << std::endl << std::endl;
        
        std::string line;
        list.clear();
        while (std::getline(textFileReader, line)) {
            list.push_back(line);
        }
        textFileReader.close();
    }
    else {
        errorLog("Unable to open the text file at: ");
        errorLog(TEXT_FILE_PATH);
        errorLog(" check for the permissions of the file or if it exists.");
        std::cout << std::endl << std::endl;
    }
    return list;
}

std::string getUserTextFilePath(ToDoList& todoList) {
    // Gets the directory from the user and validates it

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string newTextFilePath;

    while (true) {
        Log("Enter the directory path (or enter 'Q' to go back): cd ");
        std::string userInput;
        std::getline(std::cin, userInput);

        // Check if user wants to quit
        if (userInput == "Q" || userInput == "q") {
            Log('\n');
            return todoList.getTextFilePath();
        }
        // Check if the input is empty
        else if (isInputValidated(userInput) == false) {
            errorLog("Empty input. Please enter a valid path.\n");
            continue;
        }

        // Construct the full path if /list.txt is present in the input
        size_t pos = userInput.find("/list.txt");
        if (pos != std::string::npos) {
            userInput.erase(pos, std::string("/list.txt").length());
            newTextFilePath = userInput;
        }
        else {
            newTextFilePath = userInput;
        }

        // Check if the path exists
        if (doesDirectoryExist(newTextFilePath)) {
            break;
        }
        else {
            errorLog("The path does not exist.\n");
        }
    }
    return newTextFilePath + "/list.txt";
}

std::string formatPath(std::string& unformattedFilePath) {
    // Formats inputted file path or saved path to avoid reading errors

    // Replace backslashes with forward slashes
    std::string replaceThis = "\\";
    std::string replaceWith = "/";
    size_t start = 0;

    while ((start = unformattedFilePath.find(replaceThis, start)) != std::string::npos) {
        unformattedFilePath.replace(start, replaceThis.length(), replaceWith);
        start += replaceWith.length(); // Move past the replaced part
    }

    // Remove multiple forward slashes with just one
    replaceThis = "//";
    replaceWith = "/";
    start = 0;

    while ((start = unformattedFilePath.find(replaceThis, start)) != std::string::npos) {
        unformattedFilePath.replace(start, replaceThis.length(), replaceWith);
    }

    std::string formattedFilePath = unformattedFilePath;

    return formattedFilePath;
}

void saveCurrentTextFilePathToIniFile(std::string const INI_FILE_PATH, std::string const TEXT_FILE_PATH) {
    // Saves contents of the vector list to the file

    std::ofstream iniFileWriter(INI_FILE_PATH); // Path to config file

    if (iniFileWriter.is_open()) {
        iniFileWriter << "[Settings]\n";
        iniFileWriter << "LastUsedFilePath=" << TEXT_FILE_PATH;
        iniFileWriter.close();
    }
    else {
        errorLog("Unable to open the file.");
    }
}

std::string getLastUsedTextFilePathFromFile(std::string const INI_FILE_PATH) {
    // Gets last used file path in the ini file

    std::ifstream iniFileReader(INI_FILE_PATH); // Path to config file

    if (iniFileReader.is_open()) {
        std::string line;
        while (std::getline(iniFileReader, line)) {
            if (line.find("LastUsedFilePath=") != std::string::npos) {
                iniFileReader.close();

                return line.substr(17);
            }
        }
    }
    errorLog("Unable to find last used text file path. Creating new file...\n");
}

std::string getExecutablePath() {
    // Gets the path of the this exe

    std::filesystem::path currentPath = std::filesystem::current_path();
    std::string executablePath = currentPath.string();
    executablePath = formatPath(executablePath);

    return executablePath + "/";
}