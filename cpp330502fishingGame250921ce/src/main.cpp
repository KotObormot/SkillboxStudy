#include "common.h"
#include "laguna.h"

int main() {
    std::cout << "Hello!\n";

    Laguna laguna;

    std::string command;

    do {
        std::cout << "Enter PLAY, PRINT, or EXIT --> ";
        command = correctCommandInput();

        if (command == "play") {
            laguna.fishing();
            break;
        } else if (command == "print") {
            laguna.print();
        }

    } while (command != "exit");

    std::cout << "Game over. Thank you!\n";
}