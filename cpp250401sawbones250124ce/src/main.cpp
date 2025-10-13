#include <iostream>
#include <string>
#include <limits> // для std::numeric_limits
#include "operations.h"
#include "double_input.h"
#include "coordinate.h"

int main() {
    std::string command {};
    std::cout << "Let's begin the operation.";
    bool isSurgeryComplete {false};
    One_coordinate coordinates_scalpel_start {};
    One_coordinate coordinates_scalpel_finish {};
    scalpel(coordinates_scalpel_start, coordinates_scalpel_finish);
    One_coordinate coordinates_suture_start {};
    One_coordinate coordinates_suture_finish {};
    while(!isSurgeryComplete) {        
        std::cout << "Enter the following command--> ";
        std::cin.clear();
        std::cin >> command;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for(int i = 0; i < command.size(); ++i) {
            command[i] = std::tolower(command[i]);
        }
        while(command != "scalpel" 
                && command != "hemostat"
                && command != "tweezers"
                && command != "suture") {
            std::cout << "Enter the correct command finally!--> ";
            std::cin.clear();
            std::cin >> command;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            for(int i = 0; i < command.size(); ++i) {
                command[i] = std::tolower(command[i]);
            }
        }
        if(command == "hemostat") {
            One_coordinate coordinate;
            hemostat(coordinate);
        } else if(command == "tweezers") {
            One_coordinate coordinate;
            tweezers(coordinate);
        } else if(command == "suture") {
            isSurgeryComplete = suture(coordinates_suture_start, coordinates_suture_finish, coordinates_scalpel_start, coordinates_scalpel_finish);
        } else {
            std::cout << "There is already one open incision. Do you want to put a stitch? (y/n)--> ";
            char choice {};                            
            std::cin.clear();        
            std::cin >> choice;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = std::tolower(choice);
            while(choice != 'y' && choice != 'n') {
                std::cout << "Finally, specify your choice--> ";
                std::cin.clear();
                std::cin >> choice;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                choice = std::tolower(choice);
            }
            if(choice == 'y') {
                isSurgeryComplete = suture(coordinates_suture_start, coordinates_suture_finish, coordinates_scalpel_start, coordinates_scalpel_finish);                
            } else {
                std::cout << "Continue...\n";
                continue;
            }
        }
    }
    std::cout << "\nCongratulations! The surgery was a success.\n";
    return 0;
}