#pragma once

#include <string>
#include <vector>

class ToDoList {
private:
	std::vector<std::string> m_taskList;
	std::vector<bool> m_IsTaskListChecked;
	std::string m_TextFilePath;
public:
	ToDoList();

	void showMenu();
	void addToVectorList();
	void deleteFromVectorList();
	void showTheVectorList();
	void saveToFile();
	void setTextFilePath(std::string x);
	std::string getTextFilePath();
	void setTaskList(std::vector<std::string> x);
	std::vector<std::string> getTaskList();
};