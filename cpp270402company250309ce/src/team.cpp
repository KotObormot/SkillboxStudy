#include "team.h"

Team::Team() {
    std::cout << "Enter number of employees of the team ";
    numberOfEmployees = handlingIntInput();
    for(int i {0}; i < numberOfEmployees; ++i) {
        std::cout << "# " << i << ": ";
        Employee employee;
        employees.push_back({employee});
    }
    numberBusyEmployees = 0;
}

 void Team::print() {
    teamLeader.print();
    for(int i {0}; i < employees.size(); ++i) {
        employees[i].print();
    }
    std::cout << "---------------------------\n"
              << "Total number of employess " << numberOfEmployees
              << ",\n" << "Number of available employees " << (numberOfEmployees - numberBusyEmployees)
              << ".\n";
}

int Team::getNumberOfEmployess() {
    return numberOfEmployees;
}

void Team::does(int& instructionForTeam) {    
    int tasksCount {0};
    if(numberBusyEmployees == numberOfEmployees) {
        std::cout << "This team is already busy! " << "\n";
        return;
    } else {
        teamLeader.does(instructionForTeam);
        std::srand(instructionForTeam);
        int tasksCountDraft {std::rand() % numberOfEmployees + 1};
        tasksCount = (tasksCountDraft <= (numberOfEmployees - numberBusyEmployees)) 
                        ? (tasksCountDraft) 
                        : (numberOfEmployees - numberBusyEmployees);
        std::cout << "gave tasks to " << tasksCount << " employees. \n";
    }

    for(int i {0}; i < numberOfEmployees; ++i) {
        int taskForEmployee {tasksCount + i};
        if(!employees[i].getBusy() && tasksCount > 0) {
            employees[i].does(taskForEmployee);
            ++numberBusyEmployees;
            --tasksCount;
        }
    }
    if(numberBusyEmployees == numberOfEmployees) {
        std::cout << "All employees of this team are busy!\n";
    }
}

int Team::getNumberBusyEmployees() {
    return numberBusyEmployees;
}
