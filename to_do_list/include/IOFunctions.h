#pragma once

// For data types
#include <string>
#include <vector>

// Function declarations
void showMenu();
bool doesDirectoryExist(std::string const PATH);
void createFile(std::string const PATH, std::string const EXTENSTION);
void createOrOpenFileDecider(ToDoList& todoList, std::string const EXTENSION);
std::vector<std::string> importTasksFromFile(const std::string TEXT_FILE_PATH);
std::string formatPath(std::string& unformattedFilePath);
void saveCurrentTxtFilePathToIniFile(std::string const PATH);

// Getters
std::string getUserTextFilePath(ToDoList& todoList);
std::string getLastUsedTextFilePath(std::string const INI_FILE_PATH);
std::string getExecutablePath();