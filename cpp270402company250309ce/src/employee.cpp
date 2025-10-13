#include "employee.h"

Employee::Employee() {
    busy = false;
    std::cout << "Enter the name of the employee--> ";
    getline(std::cin, name);
}

void Employee::does(int& receivedTask) {
    if(busy) {
        std::cout << "The employee " << (*this).name << "(staffID " << getStaffID()
                  << ") is already busy with job " << (char)task << ".\n";
        return; 
    } else {
        std::srand(receivedTask);
        task = std::rand() % 3 + 66;
        busy = true;
        std::cout << "The employee " << this->name << " (staffID " << getStaffID()
                << ") received the task " << (char)task << ".\n";
    }
}

bool Employee::getBusy() {
    return this->busy;
}

void Employee::print() {
    std::cout << "\t\t"  << "Employee " << name 
                << " (staffID " << getStaffID() << "): " ;
    if(this->busy) {
        std::cout << " does the work " << (char)task << ".\n";
    } else {
        std::cout << " not busy = " << busy << ".\n";
    }                  
}