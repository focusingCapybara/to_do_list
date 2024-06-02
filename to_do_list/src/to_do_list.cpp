#include <iostream>
#include <cstddef> // For size_t
#include <sstream> // For getline input
#include <fstream> // For creating files
#include <vector>
#include <filesystem> // For file directories

template<typename T>
static void Log(const T& MESSAGE) {
    std::cout << MESSAGE;
}

static void AddToList(std::vector<std::string>& list) {
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

static void ShowTheList(const std::vector<std::string>& LIST) {
    Log('\n');

    if (LIST.empty()) {
        Log("Your to-do list is empty.\n\n");
        return;
    }

    size_t taskNum = 1;
    for (const std::string TASK : LIST) {
        std::cout << taskNum << ". " + TASK << '\n';
        taskNum++;
    }
    Log('\n');
}

static void SaveToFile(const std::vector<std::string>& LIST, std::string filePath) {
    if (filePath != "list.txt") {
        filePath = filePath + "/list.txt";
    }

    std::ofstream listFile(filePath);

    if (listFile.is_open()) {
        Log("\nFile opened successfully, writing to file...\n");
        
        for (const std::string TASK : LIST) {
            listFile << TASK << '\n';
        }
        listFile.close();
        Log("File has been saved.\n\n");
    }
    else {
        Log("Unable to open the file.\n");
    }
}

static void DeleteFromList(std::vector<std::string>& list) {
    size_t indexDel;
    std::string userInput;

    ShowTheList(list);

    while (!(list.empty())) {
        Log("\nEnter the task number you wish to delete (or enter 'Q' to go back): ");
        std::cin >> userInput;

        if (userInput == "Q" || userInput == "q") {
            return;
        }

        indexDel = stoul(userInput) - 1;

        if (indexDel >= 0 && indexDel < list.size()) {
            list.erase(list.begin() + indexDel);
            Log("Successfully deleted a task, updated list:");
            ShowTheList(list);
            continue;
        }
        else {
            Log("Enter a valid task number.");
            ShowTheList(list);
            continue;
        }
    }
    Log('\n');
}

static void ChangeFileDirectory(std::string& changedFilePath) {
    Log("Enter the directory path: cd ");
    std::cin >> changedFilePath;

    if (std::filesystem::exists(changedFilePath)) {
        std::filesystem::current_path(changedFilePath);
        std::ofstream listFile("list.txt");
    }
    else {
        Log("The path does not exist.\n");
    }
}

int main() {
    std::vector<std::string> list;
    std::string filePath = "list.txt", line;
    std::ifstream listFile(filePath);

    if (listFile.is_open()) {
        Log("Opened your previous text file.\n");

        while (std::getline(listFile, line)) {
            list.push_back(line);
        }
        listFile.close();
    }
    else {
        Log("Unable to open the text file.\n");
    }
    
    while (true) {
        Log("Select an option:\n");
        Log("\t1. Add to to-do list\n");
        Log("\t2. Show to-do list\n");
        Log("\t3. Delete from to-do list\n");
        Log("\t4. Save the list to file\n");
        Log("\t5. Open/create text file\n");
        Log("\t6. Quit the program\n\n");

        std::string userChoice;
        size_t userNumberChoice = 0;
        Log("My choice is: ");
        std::cin >> userChoice;

        if (userChoice == "1" || userChoice == "2" || userChoice == "3" ||
            userChoice == "4" || userChoice == "5" || userChoice == "6") {
            userNumberChoice = stoul(userChoice);
        }
        else {
            Log("Invalid input, try again.\n\n");
            continue;
        }

        switch (userNumberChoice) {
        case 1:
            AddToList(list);
            break;
        case 2:
            ShowTheList(list);
            break;
        case 3:
            DeleteFromList(list);
            break;
        case 4:
            SaveToFile(list, filePath);
            break;
        case 5:
            ChangeFileDirectory(filePath);
            break;
        case 6:
            Log("Exiting...");
            return 1;
        default:
            Log("Invalid input, try again.\n\n");
            break;
        }
    }
}