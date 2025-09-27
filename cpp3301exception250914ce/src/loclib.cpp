#include "loclib.h"

int randomNumber(int min, int max) {
    return (std::rand() % (max - min + 1)) + min;
}

double handlingDoubleInput() {
    while (true) { // Цикл, пока пользователь не введет допустимые данные
        std::cout << "-->  ";
        double x {0};
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

int handlingIntInput() {
    while (true) { // Цикл, пока пользователь не введет допустимые данные
        std::cout << "-->  ";
        double x {0};
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
    std::cin.clear();
    std::cin >> command;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for(int i = 0; i < command.size(); ++i) {
        command[i] = std::tolower(command[i]);
    }
    return command;
}

std::string correctCommandInput(const std::string& cmd) {
    std::string command {};
    while(true) {
        std::cin.clear();
        std::cin >> command;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for(int i = 0; i < command.size(); ++i) {
            command[i] = std::tolower(command[i]);
        }
        if(command == cmd) {
            return command;
        } else {
            std::cout << "Error. Please use '" << cmd << "'.\n";
        }
    }
}

const double getPI() {
    return std::atan(1.0) * 4;
    // return acos(-1.0);
}

std::string normString(const std::string& badString) {
    std::string normString{};
        for(size_t i(0); i < badString.size(); ++i) {
            normString += std::tolower(badString[i]);
        }
    return normString;
}