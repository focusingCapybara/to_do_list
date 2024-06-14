#include "../include/ToDoList.h"
#include "../include/Log.h"
#include "../include/IOFunctions.h"

#include <sstream> // For getline input and converting types
#include <fstream> // For creating files
#include <vector> // For dynamic array
#include <filesystem> // For file directories

void createOrOpenFileDecider(ToDoList& todoList) {
    // Read file
    if (std::filesystem::exists(TEXT_FILE_PATH)) {
        importTasksFromFile(TEXT_FILE_PATH);
    }
    // Create file
    else {
        createNewTextFile(TEXT_FILE_PATH);
        list.clear();
    }
}

std::vector<std::string> importTasksFromFile(const std::string TEXT_FILE_PATH) {
    std::ifstream textFileReader(TEXT_FILE_PATH);

    if (textFileReader.is_open()) {
        successLog("Opened text file at: ");
        successLog(TEXT_FILE_PATH);
        std::cout << std::endl << std::endl;

        std::vector<std::string> list;
        std::string line;
        list.clear();
        while (std::getline(textFileReader, line)) {
            list.push_back(line);
        }
        textFileReader.close();
        return list;
    }
    else {
        errorLog("Unable to open the text file at: ");
        errorLog(TEXT_FILE_PATH);
        errorLog(" check for the permissions of the file or if it exists.");
        std::cout << std::endl << std::endl;
    }
}

void createNewTextFile(const ToDoList& todoList) {
    std::ofstream fileCreator(TEXT_FILE_PATH);
    fileCreator.close();

    successLog("File has been created at: ");
    successLog(TEXT_FILE_PATH);
    std::cout << std::endl << std::endl;
}

std::string getUserTextFilePath(ToDoList& todoList) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        Log("Enter the directory path (or enter 'Q' to go back): cd ");
        std::string userInput;
        std::getline(std::cin, userInput);

        // Check if user wants to quit
        if (userInput == "Q" || userInput == "q") {
            Log('\n');
            return newTextFilePath;
        }

        // Check if the input is empty
        if (userInput.empty()) {
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
        if (std::filesystem::exists(newTextFilePath)) {
            break;
        }
        else {
            errorLog("The path does not exist.\n");
        }
    }
    return newTextFilePath + "/list.txt";
}

std::string formatPath(std::string& unformattedFilePath){
    // Formats inputted file path or saved path to avoid errors

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

void saveCurrentTextFilePath(const ToDoList& todoList) {
    std::ofstream iniFileWriter("C:/Users/kacpe/Desktop/config.ini"); // Path to config file

    if (iniFileWriter.is_open()) {
        iniFileWriter << "[Settings]\n";
        iniFileWriter << "LastUsedFilePath=" << TEXT_FILE_PATH;
        iniFileWriter.close();
    }
    else {
        errorLog("Unable to open the file.");
    }
}

std::string getLastUsedTextFilePath() {
    std::ifstream iniFileReader("C:/Users/kacpe/Desktop/config.ini"); // Path to config file

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

    // Get path where this executable is if no path has been found
    std::string executablePath = getExecutablePath();
    saveCurrentTextFilePath(executablePath);
    return executablePath;
}

std::string getExecutablePath() {
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::string executablePath = currentPath.string();
    formatPath(executablePath);

    return (executablePath + "/list.txt");
}