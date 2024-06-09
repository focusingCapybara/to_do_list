#define NOMINMAX // Otherwise it will interfere with std::max and std::min
#include <Windows.h> // For modifying the console

#include <iostream> // For input/output operations
#include <sstream> // For getline input and converting types
#include <fstream> // For creating files
#include <vector> // For dynamic array
#include <filesystem> // For file directories

// Function prototypes
template<typename T>
static void Log(const T& MESSAGE);
template<typename T>
static void pathLog(const T& MESSAGE);
template<typename T>
static void successLog(const T& MESSAGE);
template<typename T>
static void errorLog(const T& MESSAGE);

static void showMenu();
static void addToVectorList(std::vector<std::string>& list);
static void deleteFromVectorList(std::vector<std::string>& list);
static void showTheVectorList(const std::vector<std::string>& LIST);
static void saveToFile(const std::vector<std::string>& LIST, const std::string& TEXT_FILE_PATH);
static void createOrOpenFileDecider(std::vector<std::string>& list, const std::string& textFilePath);
static void importTasksFromFile(std::vector<std::string>& list, const std::string& TEXT_FILE_PATH);
static void createNewTextFile(const std::string& TEXT_FILE_PATH);
static std::string getUserTextFilePath(std::string& newFilePath);
static std::string formatPath(std::string& unformattedFilePath);
static void saveCurrentTextFilePath(const std::string& TEXT_FILE_PATH);
static std::string getLastUsedTextFilePath();
static std::string getExecutablePath();

int main() { // show what it needs to be saved, maybe use const for textFilePath
    std::string textFilePath = getLastUsedTextFilePath();
    std::vector<std::string> list;
    importTasksFromFile(list, textFilePath);

    while (true) {
        showMenu();

        std::string userChoice;
        short int userNumberChoice = 0;
        pathLog(textFilePath);
        Log("> My choice is: ");
        std::cin >> userChoice;

        try {
            userNumberChoice = stoi(userChoice);
        }
        catch (const std::exception&) {
            errorLog("Enter a number.\n\n");
            continue;
        }

        switch (userNumberChoice) {
        case 1:
            addToVectorList(list);
            break;
        case 2:
            showTheVectorList(list);
            break;
        case 3:
            deleteFromVectorList(list);
            break;
        case 4:
            saveToFile(list, textFilePath);
            break;
        case 5:
            textFilePath = getUserTextFilePath(textFilePath);
            textFilePath = formatPath(textFilePath);
            createOrOpenFileDecider(list, textFilePath);
            saveCurrentTextFilePath(textFilePath);
            break;
        case 6:
            return 0;
        default:
            errorLog("Incorrect choice, try again.\n\n");
            break;
        }
    }
}

template<typename T>
static void Log(const T& MESSAGE) {
    std::cout << MESSAGE;
}

template<typename T>
static void pathLog(const T& MESSAGE) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 1);
    std::cout << MESSAGE;
    SetConsoleTextAttribute(hConsole, 7);
}

template<typename T>
static void successLog(const T& MESSAGE) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 2);
    std::cout << MESSAGE;
    SetConsoleTextAttribute(hConsole, 7);
}

template<typename T>
static void errorLog(const T& MESSAGE) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 4);
    std::cerr << MESSAGE;
    SetConsoleTextAttribute(hConsole, 7);
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

static void addToVectorList(std::vector<std::string>& list) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string task;

    while (true) {
        Log("\nEnter your to-do task (or enter 'Q' to go back): ");
        std::getline(std::cin, task);

        if (task.empty() || std::isspace(task.front()) || std::isspace(task.back())) {
            errorLog("Cannot leave empty space at the start or at the end.\n");
        }
        else if (task == "Q" || task == "q") {
            break;
        }
        else {
            list.push_back(task);
        }
        Log('\n');
    }
}

static void deleteFromVectorList(std::vector<std::string>& list) {
    showTheVectorList(list);

    while (!(list.empty())) {
        Log("\nEnter the task number you wish to delete (or enter 'Q' to go back): ");
        std::string userChoice;
        std::cin >> userChoice;

        if (userChoice == "Q" || userChoice == "q") {
            break;
        }

        try {
            size_t indexDel = std::stoi(userChoice) - 1;
            if (indexDel < list.size()) {
                list.erase(list.begin() + indexDel);
                successLog("Successfully deleted a task, updated list:\n");
                showTheVectorList(list);
            }
            else {
                errorLog("Enter a valid task number.\n");
            }
        }
        catch (const std::exception&) {
            errorLog("Enter a number.\n");
        }
    }
    Log('\n');
}

static void showTheVectorList(const std::vector<std::string>& LIST) {
    Log('\n');

    if (LIST.empty()) {
        Log("Your to-do list is empty.\n\n");
        return;
    }

    Log("Here's your to-do list:\n");
    short int taskNum = 1;
    for (const std::string& TASK : LIST) {
        std::cout << '\t' << taskNum << ". " + TASK << '\n';
        taskNum++;
    }
    Log('\n');
}

static void saveToFile(const std::vector<std::string>& LIST, const std::string& TEXT_FILE_PATH) {
    std::ofstream fileWriter(TEXT_FILE_PATH);

    if (fileWriter.is_open()) {
        successLog("\nFile opened successfully, writing to file...\n");

        for (const std::string& TASK : LIST) {
            fileWriter << TASK << '\n';
        }
        fileWriter.close();
        successLog("File has been saved.\n\n");
    }
    else {
        errorLog("Unable to open the file.\n");
    }
}

static void createOrOpenFileDecider(std::vector<std::string>& list, const std::string& TEXT_FILE_PATH) {
    // Read file
    if (std::filesystem::exists(TEXT_FILE_PATH)) {
        importTasksFromFile(list, TEXT_FILE_PATH);
    }
    // Create file
    else {
        createNewTextFile(TEXT_FILE_PATH);
        list.clear();
    }
}

static void importTasksFromFile(std::vector<std::string>& list, const std::string& TEXT_FILE_PATH) {
    std::ifstream textFileReader(TEXT_FILE_PATH);

    if (textFileReader.is_open()) {
        successLog("Opened text file at: ");
        successLog(TEXT_FILE_PATH);
        std::cout << std::endl << std::endl;

        std::string line;
        list.clear();
        while (std::getline(textFileReader, line)) {
            list.push_back(line);
        }
        textFileReader.close();
    }
    else {
        errorLog("Unable to open the text file at: ");
        errorLog(TEXT_FILE_PATH);
        errorLog(" check for the permissions of the file or if it exists.");
        std::cout << std::endl << std::endl;
    }
}

static void createNewTextFile(const std::string& TEXT_FILE_PATH) {
    std::ofstream fileCreator(TEXT_FILE_PATH);
    fileCreator.close();

    successLog("File has been created at: ");
    successLog(TEXT_FILE_PATH);
    std::cout << std::endl << std::endl;
}

static std::string getUserTextFilePath(std::string& newTextFilePath) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        Log("Enter the directory path (or enter 'Q' to go back): cd ");
        std::string userInput;
        std::getline(std::cin, userInput);

        // Check if user wants to quit
        if (userInput == "Q" || userInput == "q") {
            Log('\n');
            return newTextFilePath;
        }

        // Check if the input is empty
        if (userInput.empty()) {
            errorLog("Empty input. Please enter a valid path.\n");
            continue;
        }

        // Construct the full path if /list.txt is present in the input
        size_t pos = userInput.find("/list.txt");
        if (pos != std::string::npos) {
            userInput.erase(pos, std::string("/list.txt").length());
            newTextFilePath = userInput;
        }
        else {
            newTextFilePath = userInput;
        }

        // Check if the path exists
        if (std::filesystem::exists(newTextFilePath)) {
            break;
        }
        else {
            errorLog("The path does not exist.\n");
        }
    }
    return newTextFilePath + "/list.txt";
}

static std::string formatPath(std::string& unformattedFilePath) {
    // Formats inputted file path or saved path to avoid errors

    // Replace backslashes with forward slashes
    std::string replaceThis = "\\";
    std::string replaceWith = "/";
    size_t start = 0;

    while ((start = unformattedFilePath.find(replaceThis, start)) != std::string::npos) {
        unformattedFilePath.replace(start, replaceThis.length(), replaceWith);
        start += replaceWith.length(); // Move past the replaced part
    }

    // Remove multiple forward slashes with just one
    replaceThis = "//";
    replaceWith = "/";
    start = 0;

    while ((start = unformattedFilePath.find(replaceThis, start)) != std::string::npos) {
        unformattedFilePath.replace(start, replaceThis.length(), replaceWith);
    }

    std::string formattedFilePath = unformattedFilePath;

    return formattedFilePath;
}

static void saveCurrentTextFilePath(const std::string& TEXT_FILE_PATH) {
    std::ofstream iniFileWriter("C:/Users/kacpe/Desktop/config.ini"); // Path to config file

    if (iniFileWriter.is_open()) {
        iniFileWriter << "[Settings]\n";
        iniFileWriter << "LastUsedFilePath=" << TEXT_FILE_PATH;
        iniFileWriter.close();
    }
    else {
        errorLog("Unable to open the file.");
    }
}

static std::string getLastUsedTextFilePath() {
    std::ifstream iniFileReader("C:/Users/kacpe/Desktop/config.ini"); // Path to config file

    if (iniFileReader.is_open()) {
        std::string line;
        while (std::getline(iniFileReader, line)) {
            if (line.find("LastUsedFilePath=") != std::string::npos) {
                iniFileReader.close();

                return line.substr(17);
            }
        }
    }
    errorLog("Unable to find last used text file path. Creating new file...\n");

    // Get path where this executable is if no path has been found
    std::string executablePath = getExecutablePath();
    saveCurrentTextFilePath(executablePath);
    return executablePath;
}

static std::string getExecutablePath() {
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::string executablePath = currentPath.string();
    formatPath(executablePath);

    return (executablePath + "/list.txt");
}