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
    std::ofstream listFile("list.txt", std::ios_base::app);
    short int taskNum = 1;

    if (listFile.is_open()) {
        std::cout << "\nFile opened successfully, writing to file...\n";
        
        for (std::string task : list) {
            listFile << taskNum << ". " + task << '\n';
            taskNum++;
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

        if (delNum < (list.size() - 1) || delNum > (list.size() - 1)) {
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

int main() {
    std::vector<std::string> list;
    std::string task = "";
    short int userChoice;

    // make a function to import the content from file
    
    while (true) {
        std::cout << "Select an option:\n";
        std::cout << "\t1. Add to to-do list\n";
        std::cout << "\t2. Show to-do list\n";
        std::cout << "\t3. Delete from to-do list\n";
        std::cout << "\t4. Save the list to file\n";
        std::cout << "\t5. Quit the program\n\n";

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