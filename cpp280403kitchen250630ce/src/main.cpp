#include "initial_conditions.h"
#include "meal.h"
#include "kitchen.h"

size_t numOfDeliveries(0);

int main() {
    std::srand(std::time(nullptr));
    std::cout << "Hello" << "\n";

    auto startTime = std::chrono::high_resolution_clock::now();

    Kitchen kitchen;
    kitchen.start();
    kitchen.join();

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = endTime - startTime;
    double timeTaken = duration.count();
    std::cout << "Total time " << timeTaken << "\n";
    
    return 0;
}
