#include <iostream>
#include <ctime>
#include <iomanip>
#include "timer.h"
#include <chrono>
#include <thread>
#include <conio.h>

void timer(size_t interval) {
   std::time_t t_timer = interval;
   while(true) {
        std::tm* tm_local = std::localtime(&t_timer);
        if(tm_local->tm_sec <= 0) {
            break;
        }
        std::time_t t_start = std::time(nullptr);
        std::tm* tm_start = std::localtime(&t_start);        
        int c_start = clock();
        std::cout << "*\n";
        
        --t_timer;

        while(true) {
            std::time_t t_finish = std::time(nullptr);
            double diff_time = std::difftime(t_finish, t_start);
            int c_finish = clock();

            if(((int)diff_time >= 1) && ((c_finish - c_start) * 1000 / CLOCKS_PER_SEC) >= 1000) {
                break;
            }
        }
   }
}

void stopwatchForWindows() {
    auto start = std::chrono::high_resolution_clock::now();
   unsigned minutes, seconds, milliseconds;
   while (true) {
       milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start).count();
       seconds = milliseconds/1000;
       milliseconds %= 100;
       minutes = seconds/60;
       seconds %= 60;
       std::cout << std::setw(2) << std::setfill('0') << minutes 
                 << ":" << std::setw(2) << std::setfill('0') << seconds 
                 << "\n";
       //std::cout << "~\n";

       std::this_thread::sleep_for(std::chrono::milliseconds(1000));
       std::system("cls");
       if (kbhit()) {
           //std::cout<<"STOP\n";
           std::cin.get();
           break;
       }
   }
   std::cout << "\nTime: " << std::setw(2) << std::setfill('0') << minutes 
             << ":" << std::setw(2) << std::setfill('0') << seconds 
             << "\n";

}