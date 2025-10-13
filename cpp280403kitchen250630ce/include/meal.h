#pragma once
#include "initial_conditions.h"

enum class Dishes {
    START,
    PIZZA,
    SOUP,
    STEAK,
    SALAD,
    SUSHI,
    TEA,
    END
};

struct Meal {
    unsigned id;
    Dishes dish;         
    bool isReady;       
    void setMeal();
    std::string getMeal();
};
