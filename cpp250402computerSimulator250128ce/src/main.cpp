#include <iostream>
#include <limits> // для std::numeric_limits
#include "kbd.h"
#include "ram.h"
#include "gpu.h"
#include "cpu.h"
#include "disk.h"
  
int main() {
    std::string command {};
    std::cout << "Welcome.\n";
    bool isGameOver {false};
    RAM ram {};
    while(!isGameOver) {        
        std::cout << "user@computer:~$ ";
        std::cin.clear();
        std::cin >> command;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for(int i = 0; i < command.size(); ++i) {
            command[i] = std::tolower(command[i]);
        }
        while(command != "sum" //вычисление суммы
                && command != "save" //сохранить в файл
                && command != "load" //загрузить из файла
                && command != "input" //ввести с клавиатуры
                && command != "display" //вывести на экран
                && command != "exit") {
            std::cout << "user@computer:~$ ";
            std::cin.clear();
            std::cin >> command;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            for(int i = 0; i < command.size(); ++i) {
                command[i] = std::tolower(command[i]);
            }
        }
        if(command == "input") {
            ram = write(kbd_input());
        } else if(command == "display") {
            gpu_out(read(ram));
        } else if(command == "sum") {
            compute(read(ram));
        } else if(command == "save") {
            save(read(ram));
        } else if(command == "exit") {
            std::cout << "Goodbye!\n";
            save(read(ram));
            isGameOver = true;
        } else if(command == "load") {
            ram = write(load());
        } 
    }
    return 0;
}