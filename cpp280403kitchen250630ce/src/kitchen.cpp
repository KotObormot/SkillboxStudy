#include "initial_conditions.h"
#include "kitchen.h"
#include "loclib.h"

Kitchen::Kitchen() 
        : orderCount(0)
        , preparedCount(0)
        , deliveredCount(0)
        , stop(false)        
{}

void Kitchen::start() {
    orderThread = std::thread(&Kitchen::receive, this);
    workerThread = std::thread(&Kitchen::cooking, this);
    courierThread = std::thread(&Kitchen::delivery, this);
}

void Kitchen::join() {
    orderThread.join();
    workerThread.join();
    courierThread.join();
}

void Kitchen::receive() {
    int receiptTime(0);
    while(true) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            if(orderCount >= TOTAL_ORDERS) {
                break;      // Maximum orders received
            }
            orderCount++;
            Meal newMeal;
            newMeal.id = orderCount;
            newMeal.setMeal();
            newMeal.isReady = false;
            orderQueue.push(newMeal);
            std::cout << "The order #" << newMeal.id 
                      << "\t" << newMeal.getMeal()
                      << " has been received (passed "
                      << receiptTime << " sec)."
                      << "\n";            
        }
        cvOrder.notify_one();
        receiptTime = randomNumber(RECEIPT_TIME_MIN, RECEIPT_TIME_MAX);
        std::this_thread::sleep_for(std::chrono::seconds(receiptTime));
    }
        // After all orders have been received, we notify the cooking flow
        {
            std::lock_guard<std::mutex> lock(mtx);
            cvOrder.notify_all();
        }
        std::cout << orderCount << " orders have been received.\n";
}

void Kitchen::cooking() {
    int cookingTime(0);
    while(true) {
        Meal currentMeal;
        {
            std::unique_lock<std::mutex> lock(mtx);
            // waiting for an order to arrive or work to be completed
            cvOrder.wait(lock, [this] {
                return !orderQueue.empty()
                        || (orderCount >= TOTAL_ORDERS
                        && preparedCount == TOTAL_ORDERS);
            });

            if(orderQueue.empty() && preparedCount == TOTAL_ORDERS) {
                break;      // All orders are made and prepared
            }

            if(!orderQueue.empty()) {
                currentMeal = orderQueue.front();
                orderQueue.pop();
                // The order has started to be prepared by the kitchen
                std::cout << "The order #" << currentMeal.id 
                          << "\t" << currentMeal.getMeal()
                          << " has started to be prepared by the kitchen."
                          << "\n";
            } else {
                continue;
            }
        }

        // Cooking the dish
        cookingTime = randomNumber(COOKING_TIME_MIN, COOKING_TIME_MAX);
        std::this_thread::sleep_for(std::chrono::seconds(cookingTime));
        {
            std::lock_guard<std::mutex> lock(mtx);
            currentMeal.isReady = true;
            readyMeals.push_back(currentMeal);
            preparedCount++;
            std::cout << "The order #" << currentMeal.id 
                      << "\t" << currentMeal.getMeal()
                      << " is ready (took "
                      << cookingTime << " sec)."
                      << "\n";
        }
        cvReady.notify_one();
        if(preparedCount >= TOTAL_ORDERS) {
            break;
        }
    }

    // Terminate the cooking thread
    {
        std::lock_guard<std::mutex> lock(mtx);
        stop = true;
    }
    cvReady.notify_all();
    cvOrder.notify_all();
    std::cout << preparedCount << " dishes prepared, the kitchen has finished its work, the cooks have gone home.\n";   
}

void Kitchen::delivery() {
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(COURIER_TIME));
        bool allDelivered(false);
        {
            std::lock_guard<std::mutex> lock(mtx);
            if(stop && readyMeals.empty()) {
                break;              // All dishes are collected and the work is completed.                
            }

            if(!readyMeals.empty()) {
                for(auto& readyMeal : readyMeals) {
                    std::cout << "The order #" << readyMeal.id
                              << "\t" << readyMeal.getMeal()
                              << " has been handed over to the courier for delivery."
                              << "\n";
                    deliveredCount++;
                }
                readyMeals.clear();

                if(deliveredCount >= TOTAL_ORDERS) {
                    allDelivered = true;
                    break;
                }
            } 
        }
        if(allDelivered) {
            break;
        }
    }
    std::cout << deliveredCount << " orders have been delivered, the courier has completed his work.\n";
}
