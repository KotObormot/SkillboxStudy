#include "swimmer.h"

std::mutex mtx;

Swimmer::Swimmer() 
        : distance(0.0), timeTaken(0.0), isFinish(false) {
    double velocity;
    std::string name;
    std::cout << "Name--> ";
    std::cin >> name;
    this->name = name;
    std::cout << "Velocity (from 0.6 to 0.95 m/s)--> ";       // 1:45-2:45. => 0,95 - 0,60 m/s
    std::cin >> velocity;
    this->velocity = velocity;
}

std::string Swimmer::getName() {
    return name;
}

double Swimmer::getVelocity() {
    return velocity;
}

double Swimmer::getDistance() {
    return distance;
}

bool Swimmer::getIsFinish() {
    return isFinish;
}

double Swimmer::getTimeTaken() {
    return timeTaken;
}

void Swimmer::timeLine() {
    auto startTime = std::chrono::high_resolution_clock::now();
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(TIME_CODE));
        {
            std::lock_guard<std::mutex> lock(mtx);
            distance += velocity * TIME_CODE;
            if(distance >= RACE_DISTANCE) {
                auto endTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<float> duration = endTime - startTime;
                timeTaken = duration.count();
                isFinish = true;
                distance = RACE_DISTANCE;
                break;
            }
        }
    }
}


