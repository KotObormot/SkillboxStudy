#include "cci.h"
#include "staff.h"
#include "ceo.h"
#include "team.h"

int main() {
    std::cout << "Hello!\n";    
    CEO ceo;
    std::vector<Team> teams {};

    std::cout << "Specify the number of teams";
    int teamsNumber {handlingIntInput()};
    
    for(int i {0}; i < teamsNumber; ++i) {
        std::cout << "Team # " << i << ": ";
        Team oneTeam;
        teams.push_back({oneTeam});
    }

    int instruction {0};
    while(true) {
        int numberOfAllEmployees {0};
        int numberOfAllBusyEmpoloyees {0};
        for(int i {0}; i < teamsNumber; ++i) {
            numberOfAllEmployees += teams[i].getNumberOfEmployess();
            numberOfAllBusyEmpoloyees += teams[i].getNumberBusyEmployees();
        }
        if(numberOfAllBusyEmpoloyees == numberOfAllEmployees) {
            std::cout << "==============\nAll employess of all teams are busy.\n";
            break;
        } else {
            std::cout << "\n============\n";
            ceo.does(instruction);
        }

        for(int i {0}; i < teamsNumber; ++i) {
            std::cout << "\n------------\n";
            std::cout << "Team # " << i << ": ";
            teams[i].does(instruction);
        } 
    }
    
    std::cout << "\n\n*******************\nSo, ";
    ceo.print();
    for(int i {0}; i < teams.size(); ++i) {
        std::cout << "Team # " << i << ":\n\t";
        teams[i].print();
    }

    return 0;
}