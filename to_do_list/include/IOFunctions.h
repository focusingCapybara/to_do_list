#pragma once

#include <string>
#include <vector>

// Function declaration
void createOrOpenFileDecider(ToDoList& todoList);
std::vector<std::string> importTasksFromFile(const std::string TEXT_FILE_PATH);
void createNewTextFile(const ToDoList& todoList);
std::string formatPath(std::string& unformattedFilePath);
void saveCurrentTextFilePath(const ToDoList& todoList);

// Getters
std::string getUserTextFilePath(ToDoList& todoList);
std::string getLastUsedTextFilePath();
std::string getExecutablePath();