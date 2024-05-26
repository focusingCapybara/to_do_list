#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

template<typename T>
static void Log(const T& message) {
    std::cout << message;
}

static void addToList(std::vector<std::string>& list) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string task = "";

    while (true) {
        Log("\nEnter your to-do task (or enter 'Q' to exit): ");
        std::getline(std::cin, task);

        if (task == "Q" || task == "q") {
            break;
        }
        else if (!(task.empty())) {
            list.push_back(task);
        }
        else {
            Log("Task cannot be empty.\n");
        }
    }
}

static void showTheList(const std::vector<std::string>& list) {
    Log('\n');

    if (list.size() == 0) {
        Log("Your to-do list is empty.\n\n");
        return;
    }

    short int taskNum = 1;
    for (const std::string task : list) {
        std::cout << taskNum << ". " + task << '\n';
        taskNum++;
    }
    Log('\n');
}

static void saveToFile(const std::vector<std::string>& list) {
    std::ofstream listFile("list.txt");

    if (listFile.is_open()) {
        Log("\nFile opened successfully, writing to file...\n");
        
        for (const std::string task : list) {
            listFile << task << '\n';
        }
        listFile.close();
        Log("File has been saved.\n\n");
    }
    else {
        Log("Unable to open the file.\n");
    }
}

static void deleteFromList(std::vector<std::string>& list) {
    short int indexDel;
    std::string userInput = "";

    showTheList(list);

    while (!(list.empty())) {
        Log("\nEnter the task number you wish to delete (or enter 'Q' to go back): ");
        std::cin >> userInput;

        if (userInput == "Q" || userInput == "q") {
            return;
        }

        indexDel = stoi(userInput) - 1;

        if (indexDel < 0 || indexDel > (list.size() - 1)) {
            Log("Enter a valid task number.");
            showTheList(list);
            continue;
        }

        list.erase(list.begin() + indexDel);
        Log("Successfully deleted a task, updated list:");
        showTheList(list);
        continue;
    }
    Log('\n');
    Log("Your to-do list is empty.\n\n");
}


int main() {
    std::vector<std::string> list;
    std::ifstream listFile("list.txt");
    std::string line = "";

    if (listFile.is_open()) {
        while (std::getline(listFile, line)) {
            list.push_back(line);
        }
        listFile.close();
    }
    else {
        Log("Unable to open the txt file. A new file will be created upon saving.\n");
    }
    
    while (true) {
        Log("Select an option:\n");
        Log("\t1. Add to to-do list\n");
        Log("\t2. Show to-do list\n");
        Log("\t3. Delete from to-do list\n");
        Log("\t4. Save the list to file\n");
        Log("\t5. Quit the program\n\n");

        short int userChoice;
        Log("My choice is: ");
        std::cin >> userChoice;

        switch (userChoice) {
        case 1:
            addToList(list);
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
            Log("Exiting...");
            return 1;
        default:
            Log("Invalid input, try again.\n\n");
            break;
        }
    }
}