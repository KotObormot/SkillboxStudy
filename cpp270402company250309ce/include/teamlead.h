#pragma once
#include "staff.h"

class TeamLeader: public Staff {
  protected:
  public:
    TeamLeader();
    void print() override;
    void does(int&) override;
};