#include <iostream>
#include <ctime>
#include <iomanip>
#include "timer.h"
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>

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

using namespace std;

void setInputMode() {
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt);
    newt.c_lflag &= ~(ICANON | ECHO); // Отключаем канонический режим и эхо
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void resetInputMode() {
    struct termios newt;
    tcgetattr(STDIN_FILENO, &newt);
    newt.c_lflag |= (ICANON | ECHO); // Включаем канонический режим и эхо
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void stopWatchForLinux() {
    setInputMode(); // Устанавливаем режим ввода

    //cout << "Секундомер запущен. Нажмите Enter для остановки." << endl;
    
    auto start = chrono::steady_clock::now();
    bool running = true;

    while (running) {
        // Проверяем, была ли нажата клавиша Enter
        if (cin.peek() == '\n') {
            cin.get(); // Считываем нажатую клавишу
            running = false; // Останавливаем секундомер
        }

        // Вычисляем прошедшее время
        auto now = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(now - start).count();

        cout << "\rDuration: " << elapsed << " sec." << flush;
        this_thread::sleep_for(chrono::milliseconds(100)); // Задержка для уменьшения нагрузки на процессор
    }

    resetInputMode(); // Сбрасываем режим ввода

    //cout << "\nСекундомер остановлен." << endl;
}