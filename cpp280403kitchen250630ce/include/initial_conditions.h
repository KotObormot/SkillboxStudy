#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits> // для std::numeric_limits
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iomanip>
#include <ctime>
#include <cstdlib>

const size_t TOTAL_ORDERS(10);      //NUMBER_OF_DELIVERIES(10);   // 10 successful deliveries
const int RECEIPT_TIME_MAX(10);          // 10 sec
const int RECEIPT_TIME_MIN(5);          //  5 sec
const int COOKING_TIME_MAX(15);          // 15 sec
const int COOKING_TIME_MIN(5);          //  5 sec
const int COURIER_TIME(30);             // 30 sec