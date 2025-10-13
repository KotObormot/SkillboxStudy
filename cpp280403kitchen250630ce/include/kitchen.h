#pragma once
#include "meal.h"

class Kitchen {
  private:
    std::mutex mtx;
    std::condition_variable cvOrder;  // To notify about a new order
    std::condition_variable cvReady;  // For notification of ready meal
    std::queue<Meal> orderQueue;      // Queue of received orders for preparation
    std::vector<Meal> readyMeals;     //  Ready meals for courier delivery

    size_t orderCount;                // Number of orders received
    size_t preparedCount;             // Number of dishes prepared
    size_t deliveredCount;            // Number of dishes delivered
    bool stop;                        // Completion flag

    std::thread orderThread;          // flow of accepted orders
    std::thread workerThread;         // cooking flow
    std::thread courierThread;        // delivery flow

    void receive();                   // receipt of order 
    void cooking();                   // cooking
    void delivery();                  // courier service

  public:
    Kitchen();
    ~Kitchen() = default;
    void start();
    void join();
};