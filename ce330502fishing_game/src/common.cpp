#include <limits> // для std::numeric_limits
#include "common.h"

size_t handlingInput() {
    while (true) { // Цикл, пока пользователь не введет допустимые данные
        std::cout << "-->  ";
        size_t x {0};
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

std::string correctCommandInput() {
    std::string command {};
//    std::cin.clear();
    std::cin >> command;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for(int i = 0; i < command.size(); ++i) {
        command[i] = std::tolower(command[i]);
    }
    return command;
}
