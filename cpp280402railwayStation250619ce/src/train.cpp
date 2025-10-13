#include "initial_conditions.h"
#include "train.h"
#include "cci.h"

std::mutex mtx;
std::condition_variable cv;
bool isPlatformFree(true); 

Train::Train(char designation) 
        : designation(designation), isArrived(false), isOnPlatform(false), isDeparted(false) {
    this->designation = designation;    
    std::cout << "Train " << designation << ": ";    
    int travelTime{handlingIntInput()};
    this->travelTime = travelTime;
}

void Train::arrival() {
    // Arrival simulation
    std::this_thread::sleep_for(std::chrono::seconds(travelTime));
    {
        std::unique_lock<std::mutex> lock(mtx);
        isArrived = true;        
        std::cout << "The train " << designation << " arrived at the station."
                  << "\n";    

        //  Waiting for the platform to clear
        while(!isPlatformFree) {
            std::cout << "The train " << designation 
                    << " is waiting for the platform to become available."
                    << "\n";
            cv.wait(lock);
        }
        // Capture of the platform
        isPlatformFree = false;
        isOnPlatform = true;
        std::cout << "The train " << designation << " is occupying the platform."
                << "\n";
    }
}

void Train::wait() {
    arrival();
    // Waiting for the 'depart' command to depart
    while(true) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            if(isDeparted) {
                break;
            }
        }
        // departure time = 100 milliseconds 
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void depart(std::vector<Train>& trains) {
    size_t remainingTrains(trains.size());
    while(true) {
        if(remainingTrains == 0) {
            break;
        }

        std::string cmd(correctCommandInput("depart"));

//        {
            std::unique_lock<std::mutex> lock(mtx);
            bool foundTrain = false;
            for (auto& train : trains) {
                if (train.getIsArrived() 
                        && !train.getIsDeparterd() 
                        && train.getIsOnPlatform()) {
                    // This train is leaving the platform
                    train.setIsDeparted(true);
                    train.setIsOnPlatform(false);
                    remainingTrains--;
                    isPlatformFree = true;
                    std::cout << "Train " << train.getDesignation() << " departs from the platform.\n" ;
                    cv.notify_all();
                    foundTrain = true;
                    break;
                }
            }
            if (!foundTrain) {
                std::cout << "There is no train on the platform for departure or all have already been dispatched.\n";
            }
//        }
    }
}

char Train::getDesignation() {
    return designation;
}

bool Train::getIsArrived() {
    return isArrived;
}

bool Train::getIsOnPlatform() {
    return isOnPlatform;
}

void Train::setIsOnPlatform(bool isOnPlatform) {
    this->isOnPlatform = isOnPlatform;
}

bool Train::getIsDeparterd() {
    return isDeparted;
}

void Train::setIsDeparted(bool isDeparted) {
    this->isDeparted = isDeparted;
}
