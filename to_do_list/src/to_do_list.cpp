#define NOMINMAX // Fixes a problem at line 29
#include <Windows.h>

#include <iostream> // For input/output operations
#include <sstream> // For getline input and converting types
#include <fstream> // For creating files
#include <vector> // For dynamic array
#include <filesystem> // For file directories

template<typename T>
static void Log(const T& MESSAGE) {
    std::cout << MESSAGE;
}

static void showMenu() {
    Log("==========\n");
    Log("To-Do List\n");
    Log("==========\n\n");
    Log("Select an option:\n");
    Log("\t1. Add to-do task\n");
    Log("\t2. Show to-do list\n");
    Log("\t3. Delete from to-do list\n");
    Log("\t4. Save the list to file\n");
    Log("\t5. Open/create text file\n");
    Log("\t6. Quit the program\n\n");
}

static void addToVector(std::vector<std::string>& list) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string task = "";

    while (true) {
        Log("\nEnter your to-do task (or enter 'Q' to exit): ");
        std::getline(std::cin, task);

        if (task == "Q" || task == "q") {
            Log('\n');
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

static void showTheVectorList(const std::vector<std::string>& LIST) {
    Log('\n');

    if (LIST.empty()) {
        Log("Your to-do list is empty.\n\n");
        return;
    }

    short int taskNum = 1;
    for (const std::string TASK : LIST) {
        std::cout << taskNum << ". " + TASK << '\n';
        taskNum++;
    }
    Log('\n');
}

static void saveToFile(const std::vector<std::string>& LIST, const std::filesystem::path FILE_PATH) {
    std::ofstream fileWriter(FILE_PATH);

    if (fileWriter.is_open()) {
        Log("\nFile opened successfully, writing to file...\n");

        for (const std::string TASK : LIST) {
            fileWriter << TASK << '\n';
        }
        fileWriter.close();
        Log("File has been saved.\n\n");
    }
    else {
        Log("Unable to open the file.\n");
    }
}

static void deleteFromVector(std::vector<std::string>& list) {
    short int indexDel;
    std::string userInput;

    showTheVectorList(list);

    while (!(list.empty())) {
        Log("\nEnter the task number you wish to delete (or enter 'Q' to go back): ");
        std::cin >> userInput;

        if (userInput == "Q" || userInput == "q") {
            return;
        }

        indexDel = stoi(userInput) - 1;

        if (indexDel >= 0 && indexDel < list.size()) {
            list.erase(list.begin() + indexDel);
            Log("Successfully deleted a task, updated list:");
            showTheVectorList(list);
            continue;
        }
        else {
            Log("Enter a valid task number.");
            showTheVectorList(list);
            continue;
        }
    }
    Log('\n');
}

static std::filesystem::path formatPath(std::string unformattefFilePath) {
    // Gets the path and removes '\' at the start and at the end
    size_t start = unformattefFilePath.find("\"") + 1;
    size_t end = unformattefFilePath.find_last_of("\"");
    std::string filePath = unformattefFilePath.substr(start, end - start);

    return filePath;
}

static void saveCurrentTextFilePath(std::filesystem::path& filePath) {
    std::ofstream iniFileWriter("C:/Users/kacpe/Desktop/config.ini"); // Path to config file

    if (iniFileWriter.is_open()) {
        iniFileWriter << "[Settings]\n";
        iniFileWriter << "LastUsedFilePath=" << filePath;
        iniFileWriter.close();
    }
    else {
        Log("Unable to open the file.");
    }
}

static void importTasksFromFile(std::vector<std::string>& list, const std::filesystem::path FILE_PATH) {
    std::ifstream textFileReader(FILE_PATH);

    if (textFileReader.is_open()) {
        Log("Opened text file at: ");
        Log(FILE_PATH);
        std::cout << std::endl << std::endl;

        std::string line;
        list.clear();
        while (std::getline(textFileReader, line)) {
            list.push_back(line);
        }
        textFileReader.close();
    }
    else {
        Log("Unable to open the text file at: ");
        Log(FILE_PATH);
        Log(" check for the permissions of the file or if it exists. ");
        std::cout << std::endl << std::endl;
    }
}

static void openTextFilePath(std::vector<std::string>& list, std::filesystem::path& newFilePath) {
    Log("Enter the directory path: cd ");
    std::cin >> newFilePath;
    newFilePath += "/list.txt";

    // Read file
    if (std::filesystem::exists(newFilePath)) {
        importTasksFromFile(list, newFilePath);
    }
    // Create file
    else if (std::filesystem::exists(newFilePath.replace_filename(""))) {
        newFilePath += "list.txt";

        std::ofstream createTextFile(newFilePath);
        createTextFile.close();

        Log("Created text file at: ");
        Log(newFilePath);
        std::cout << std::endl << std::endl;

        list.clear();
    }
    else {
        Log("The path does not exist.\n");
    }
}

static std::filesystem::path getExecutablePath() { // Needs to be changed
    std::filesystem::path executablePath = std::filesystem::current_path();
    return executablePath;
}

static std::filesystem::path getLastUsedTextFilePath() {
    std::ifstream iniFileReader("C:/Users/kacpe/Desktop/config.ini"); // Path to config file

    if (iniFileReader.is_open()) {
        std::string line;
        while (std::getline(iniFileReader, line)) {
            if (line.find("LastUsedFilePath=") != std::string::npos) {
                iniFileReader.close();

                std::filesystem::path formattedFilePath = formatPath(line);

                return formattedFilePath;
            }
        }
    }
    else {
        Log("Unable to find last used text file path. Creating new file...");
    }
    // Used to create text file where this executable is if no path has been found
    return getExecutablePath();
}

int main() {
    std::filesystem::path filePath = getLastUsedTextFilePath();
    std::vector<std::string> list;
    importTasksFromFile(list, filePath);

    while (true) {
        showMenu();

        std::string userChoice;
        short int userNumberChoice = 0;
        Log(filePath);
        Log("> My choice is: ");
        std::cin >> userChoice;

        if (userChoice == "1" || userChoice == "2" || userChoice == "3" ||
            userChoice == "4" || userChoice == "5" || userChoice == "6" ||
            userChoice == "7") {
            userNumberChoice = stoi(userChoice);
        }
        else {
            Log("Invalid input, try again.\n\n");
            continue;
        }

        switch (userNumberChoice) {
        case 1:
            addToVector(list);
            break;
        case 2:
            showTheVectorList(list);
            break;
        case 3:
            deleteFromVector(list);
            break;
        case 4:
            saveToFile(list, filePath);
            break;
        case 5:
            openTextFilePath(list, filePath);
            saveCurrentTextFilePath(filePath);
            break;
        case 6:
            return 1;
        default:
            Log("Invalid input, try again.\n\n");
            break;
        }
    }
}