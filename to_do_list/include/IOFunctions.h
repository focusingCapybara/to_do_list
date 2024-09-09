#pragma once

// For data types
#include <string>
#include <vector>

// Function declarations
void showMenu();
bool isInputValidated(std::string const X);
bool doesDirectoryExist(std::string const PATH);
void createOrOpenTextFile(ToDoList& todoList);
void createFile(std::string const FULL_PATH);
void createOrOpenFileDecider(ToDoList& todoList);
std::vector<std::string> importTasksFromFile(std::string const TEXT_FILE_PATH);
std::string formatPath(std::string& unformattedFilePath);
void saveCurrentTextFilePathToIniFile(std::string const INI_FILE_PATH, std::string const TEXT_FILE_PATH);

// Getters
std::string getUserTextFilePath(ToDoList& todoList);
std::string getLastUsedTextFilePathFromFile(std::string const INI_FILE_PATH);
std::string getExecutablePath();