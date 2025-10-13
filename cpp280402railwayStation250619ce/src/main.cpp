#include "initial_conditions.h"
#include "train.h"

int main() {
    std::cout << "Hello" << "\n";
    std::cout << "Enter the travel time to the station (in seconds) for each train.\n";

    char symbol0('A');
    std::vector<Train> trains;
    for(size_t i(0); i < NUMBER_OF_TRAINS; ++i) {
        Train oneTrain(symbol0 + i);
        trains.emplace_back(oneTrain);
    }
    std::cout << "\n=====================\n";
    for(auto& train : trains) {
        std::cout << "The train " 
                  << train.getDesignation()
                  << " started moving."
                  << "\n";
    }
    std::cout << "After the train arrives at the station, give the command 'depart' to depart it out of the station."
              << "\n";

    //  Threads are launched for each train
    std::vector<std::thread> threads;

    for(auto& train : trains) {
        threads.emplace_back(&Train::wait, std::ref(train));
    }

    std::thread thrdDepart(depart, std::ref(trains));
    if(thrdDepart.joinable()) {
        thrdDepart.join();
    }

    for(auto& th : threads) {
        if(th.joinable()) {
            th.join();
        }
    }

    std::cout << "\nAll trains have departed. Station operations are closed.\n";
    return 0;
}
