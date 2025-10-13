#include "teamlead.h"

TeamLeader::TeamLeader()  {
    std::cout << "Enter the name of the leader of the team--> ";
    getline(std::cin, name);
}

void TeamLeader::print() {
    std::cout << "Team leader " << name << " (staffID " << getStaffID() << ") "
              << " break these tasks down into subtasks and assign them to their subordinates: "
              << "\n";
}

void TeamLeader::does(int& instructionFromTeamLead) {
    instructionFromTeamLead += getStaffID();
    std::cout << "The team leader ";
}