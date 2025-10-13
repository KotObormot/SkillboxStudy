#include "loclib.h"
#include "initial_conditions.h"

int randomNumber(int min, int max) {
    return (std::rand() % (max - min + 1)) + min;
}