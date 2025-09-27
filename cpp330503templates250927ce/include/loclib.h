#pragma once
//#include "common.h"

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits> // для std::numeric_limits

int randomNumber(int, int);

std::string correctCommandInput();

std::string correctCommandInput(const std::string&);

std::string normString(const std::string&);

const double getPI();

const double getE();

template<typename T>
T handlingInput(T k) {
    while (true) { // Цикл, пока пользователь не введет допустимые данные
        std::cout << "-->  ";
        T x {0};
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