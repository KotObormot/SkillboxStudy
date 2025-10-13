#pragma once
#include <vector>
#include "teamlead.h"
#include "employee.h"


class Team {
  private:
    int numberOfEmployees; // численность работников
    int numberBusyEmployees;
    TeamLeader teamLeader;
    std::vector<Employee> employees;
  public:
    Team();
    int getNumberOfEmployess();
    void print();
    void does(int& instuctionForTeam);
    int getNumberBusyEmployees();
};