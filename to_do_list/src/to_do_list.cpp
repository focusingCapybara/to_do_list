#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

static void addToList(std::vector<std::string> &list, std::string task) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::cout << "\nEnter your to-do task (or enter 'Q' to exit): ";
        std::getline(std::cin, task);

        if (task == "Q" || task == "q") {
            break;
        }
        list.push_back(task);
    }
}

static void showTheList(const std::vector<std::string> list) {
    short int taskNum = 1;

    std::cout << '\n';

    for (std::string task : list) {
        std::cout << taskNum << ". " + task << '\n';
        taskNum++;
    }
    std::cout << '\n';
}

static void saveToFile(const std::vector<std::string> list) {
    std::ofstream listFile("list.txt");
    short int taskNum = 1;

    if (listFile.is_open()) {
        std::cout << "\nFile opened successfully, writing to file...\n";
        
        for (std::string task : list) {
            listFile << task << '\n';
        }
        listFile.close();
        std::cout << "File has been saved.\n\n";
    }
    else {
        std::cout << "Unable to open the file.\n";
    }
}

static void deleteFromList(std::vector<std::string> &list) {
    short int delNum;

    try {
        showTheList(list);
        std::cout << "\nEnter the task number you wish to delete: ";
        std::cin >> delNum;

        if ((delNum - 1) < 0 || (delNum - 1) > (list.size() - 1)) {
            throw 0;
        }

        list.erase(list.begin() + (delNum - 1));
    }
    catch (...) {
        std::cout << "Enter valid task number.";
        deleteFromList(list);
    }
    std::cout << "Successfully deleted a task, updates list:";
    showTheList(list);
}

static void userMenuLog(std::string message) {
    std::cout << message;
}

int main() {
    std::vector<std::string> list;
    std::string task = "", line = "";
    short int userChoice;
    std::ifstream listFile("list.txt");

    if (listFile.is_open()) {
        while (std::getline(listFile, line)) {
            list.push_back(line);
        }
    }
    else {
        std::cout << "Unable to open the file.\n";
    }
    listFile.close();
    
    while (true) {
        userMenuLog("Select an option:\n");
        userMenuLog("\t1. Add to to-do list\n");
        userMenuLog("\t2. Show to-do list\n");
        userMenuLog("\t3. Delete from to-do list\n");
        userMenuLog("\t4. Save the list to file\n");
        userMenuLog("\t5. Quit the program\n\n");

        std::cout << "My choice is: ";
        std::cin >> userChoice;

        switch (userChoice) {
        case 1:
            addToList(list, task);
            break;
        case 2:
            showTheList(list);
            break;
        case 3:
            deleteFromList(list);
            break;
        case 4:
            saveToFile(list);
            break;
        case 5:
            std::cout << "Exiting...";
            return 1;
        default:
            std::cout << "Invalid input, try again.\n\n";
            break;
        }
    }
}