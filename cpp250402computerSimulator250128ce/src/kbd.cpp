#include <iostream>
#include <limits> // для std::numeric_limits
#include "kbd.h"
#include "ram.h"

int handling_invalid_input() {
    while (true) { // Цикл, пока пользователь не введет допустимые данные
        std::cout << "-->  ";
        int x {};
        std::cin >> x;
        // Проверяем на неудачное извлечение
        if (std::cin.fail()) { // предыдущее извлечение не удалось?        
            // да, давайте разберемся с ошибкой
            std::cin.clear(); // возвращаем нас в "нормальный" режим работы
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');     // и удаляем неверные входные данные
            std::cout << "Oops, that input is invalid.  Please try again: ";
        }   
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');; // удаляем любые посторонние входные данные
            return x;
        }
    }   
}

RAM kbd_input() {
    RAM kbd;
    std::cout << "enter 8 numbers: ";
    kbd.i0 = handling_invalid_input();
    kbd.i1 = handling_invalid_input();
    kbd.i2 = handling_invalid_input();
    kbd.i3 = handling_invalid_input();
    kbd.i4 = handling_invalid_input();
    kbd.i5 = handling_invalid_input();
    kbd.i6 = handling_invalid_input();
    kbd.i7 = handling_invalid_input();
    return kbd;
}


