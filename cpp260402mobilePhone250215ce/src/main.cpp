#include <iostream>
#include "address.h"
#include "phone.h"
#include "cci.h"

int main() {
    std::cout << "Hello! Press the ON button to turn on --> ";
    std::string onButton = correctCommandInput();
    while(onButton != "on") {
        std::cout << "Press the ON button--> ";
        onButton = correctCommandInput();
    }

    Phone newBook;
    if(!newBook.loadBook()) {
        std::cout << "OK\n";
    } else {
        std::cout << "Fill out the phone book!\n";
    }

    bool isGameOver {false};
    while(!isGameOver) {        
        std::cout << "\n==================\nCommand: (ADD / CALL / SMS / OFF)--> ";
        std::string command {correctCommandInput()};
        while(command != "add" 
                && command != "call"
                && command != "sms"
                && command != "off"
                && command != "print") {
            std::cout << "Try again--> ";
            command = correctCommandInput();
        }
        if(command == "add") {
            newBook.addAddressInBook();
        } else if(command == "off") {
            newBook.saveBook();
            std::cout << "The phone is turned off. Goodbye!\n";
            isGameOver = true;
        } else if(command == "call") {
            newBook.call();            
        } else if(command == "sms") {
            newBook.sms();
        } else if(command == "print") {
            newBook.show();
        }
    }

    return 0;
}