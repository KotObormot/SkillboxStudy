#include "staff.h"

#if DEBUG
#else
unsigned Staff::staffNumber = 0;
#endif

Staff::Staff() {
    staffID = staffNumber;
    ++staffNumber;
}

std::string Staff::getName() {
    return name;
}

unsigned Staff::getStaffNumber() {
    return staffNumber;
}

unsigned Staff::getStaffID() {
    return staffID;
}
