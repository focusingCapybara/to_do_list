#include "../include/ToDoList.h"
#include "../include/IOFunctions.h"
#include "../include/Log.h"

int main() {
    ToDoList todoList;

    while (true) {
        showMenu();

        pathLog(todoList.getTextFilePath());
        Log("> My choice is: ");
        std::string userChoice;
        std::cin >> userChoice;
        short int userNumberChoice;

        try {
            userNumberChoice = stoi(userChoice);
        }
        catch (const std::exception&) {
            errorLog("Enter a number.\n\n");
            continue;
        }

        // User options
        switch (userNumberChoice) {
        case 1:
            todoList.addToVectorList();
            break;
        case 2:
            todoList.showTheVectorList();
            break;
        case 3:
            todoList.deleteFromVectorList();
            break;
        case 4:
            todoList.saveToFile();
            break;
        case 5:
            createOrOpenTextFile(todoList);
            break;
        case 6:
            // Exit
            return 0;
        default:
            errorLog("Number out of range, try again.\n\n");
            break;
        }
    }
}