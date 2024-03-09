#include <iostream>
#include <fstream>
#include <string>
#include <limits>

void addEntry(const std::string& Filename, std::string& task) {
    std::ofstream file(Filename, std::ios::app); // Open in append mode
    file << task << std::endl;
    file.close();
}

bool FindFile(const std::string& filename, const std::string& searchString) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(searchString) != std::string::npos) {
            return true;
        }
    }
    return false;
}

void RemoveEntry(const std::string& filename, const std::string& searchString, bool& flash) {
    if (!FindFile(filename, searchString)) {
        std::cout << "Entry not found." << std::endl;
        return;
    }
    char temp;
    std::cout << "Confirm y/n : ";
    std::cin >> temp;
    switch (temp) {
    case 'y':
        std::cout << "Removing Entry" << std::endl;
        flash = true;
        break;
    case 'n':
        std::cout << "Confirmation Denied" << std::endl;
        flash = false;
        return;
    default:
        std::cout << "Invalid" << std::endl;
        flash = false;
        return;
    }

    std::ifstream inputFile(filename);
    std::ofstream tempFile(filename + ".tmp");
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.find(searchString) == std::string::npos)
            tempFile << line << std::endl;
    }
    inputFile.close();
    tempFile.close();
    std::remove(filename.c_str());
    std::rename((filename + ".tmp").c_str(), filename.c_str());
}

int main() {
    const std::string FName = "Tasks.txt";
    int choice;
    std::string task;
    bool flash = false;
    std::ifstream file; // Declare file object outside the switch

    while (true) {
        std::cout << "Welcome, Traveler" << std::endl;
        std::cout << "1. Add Task" << std::endl;
        std::cout << "2. Mark task as done" << std::endl;
        std::cout << "3. Remove task" << std::endl;
        std::cout << "4. View tasks" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter : ";

        if (std::cin >> choice) {
            switch (choice) {
            case 1:
                std::cout << "Adding Entry" << std::endl;
                do {
                    std::cout << "Enter task : ";
                    std::cin.ignore();
                    std::getline(std::cin, task);
                    if (task.empty()) {
                        std::cout << "\aInvalid Input" << std::endl;
                        continue;
                    }
                    addEntry(FName, task);
                    break;
                } while (true);
                break;
            case 2:
                do {
                    std::cout << "Enter task : ";
                    std::cin.ignore();
                    std::getline(std::cin, task);
                    if (task.empty()) {
                        std::cout << "\aInvalid Input" << std::endl;
                        continue;
                    }
                    RemoveEntry(FName, task, flash);
                    if (flash == true) {
                        std::cout << "Entry Marked as done" << std::endl;
                    }
                    break;
                } while (true);
                break;
            case 3:
                do {
                    std::cout << "Enter task : ";
                    std::cin.ignore();
                    std::getline(std::cin, task);
                    if (task.empty()) {
                        std::cout << "Invalid Input" << std::endl;
                        continue;
                    }
                    RemoveEntry(FName, task, flash);
                    if (flash == true) {
                        std::cout << "Entry Removed successfully" << std::endl;
                    }
                    break;
                } while (true);
                break;
            case 4:
                file.open(FName); // Open the file inside case 4
                if (file.is_open()) {
                    std::string line;
                    std::cout << "Viewing Entries:" << std::endl;
                    while (std::getline(file, line)) {
                        std::cout << line << std::endl;
                    }
                    file.close();
                }
                else {
                    std::cout << "Unable to open file." << std::endl;
                }
                break;
            case 5:
                std::cout << "Exiting........................." << std::endl;
                return 0; // Exit the program
            default:
                std::cout << "\aInvalid choice. Please try again." << std::endl;
                break;
            }
        }
        else {
            // If input is not an integer
            std::cout << "\aInvalid Input, please enter a valid integer" << std::endl;
            // Clear the input stream
            std::cin.clear();
            // Discard the invalid input
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return 0;
}