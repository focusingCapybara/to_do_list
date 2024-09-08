#pragma once

// For data types
#include <string>
#include <vector>

class ToDoList {
private:
	// Members
	std::vector<std::string> m_taskList;
	std::vector<bool> m_IsTaskListChecked;
	std::string m_TextFilePath;

	// Method
	void initializeClass();
public:
	// Constructor
	ToDoList();

	// Methods
	void addToVectorList();
	void deleteFromVectorList();
	void emptyVectorList();
	void showTheVectorList();
	void saveToFile();
	void setTextFilePath(std::string x);
	std::string getTextFilePath();
	void setTaskList(std::vector<std::string> x);
	std::vector<std::string> getTaskList();
};