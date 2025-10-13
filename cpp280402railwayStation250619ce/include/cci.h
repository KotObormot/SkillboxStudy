#pragma once
#include "initial_conditions.h"

#define USED false

std::string correctCommandInput();
std::string correctCommandInput(const std::string&);

#if USED
double handlingDoubleInput();
#endif
int handlingIntInput();