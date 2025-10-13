#include "initial_conditions.h"
#include "meal.h"
#include "loclib.h"

void Meal::setMeal() {
    // Counting dishes
    int countMeals(0);
    for (int i = static_cast<int>(Dishes::START) + 1; i < static_cast<int>(Dishes::END); ++i) {
        countMeals++;
    }
    if(countMeals > 0) {
        int numMeal(randomNumber(1, countMeals));
        dish = static_cast<Dishes>(static_cast<int>(numMeal));
    }
}

std::string Meal::getMeal() {
    switch (dish) {
        case Dishes::PIZZA:
            return "pizza";
        case Dishes::SALAD:
            return "salad";
        case Dishes::SOUP:
            return "soupe";
        case Dishes::STEAK:            
            return "steak";
        case Dishes::SUSHI:
            return "sushi";
        case Dishes::TEA:
            return "tea";
        default:
            return "no order";
    }
}
