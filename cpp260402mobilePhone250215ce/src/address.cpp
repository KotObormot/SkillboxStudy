#include <iostream>
#include "address.h"

void Address::setPhone(std::string phone) {
    this->phone = phone;
}

void Address::setName(std::string name) {
    this->name = name;
}

std::string Address::getPhone() {
    return this->phone;
}

std::string Address::getName() {
    return this->name;
}

Address::Address(std::string phone, std::string name): phone(phone), name(name) {}

Address::Address(): Address("", "") {};

Address::Address(const Address& addrss) {
    this->name = addrss.name;
    this->phone = addrss.phone;
} 

Address::~Address() {};

Address Address::addAddress() {    
    std::cout << "Add a contact: enter the phone number with format +7<10 digits>--> ";
    getline(std::cin, this->phone);
    
    return addAddress(this->phone);
}

Address Address::addAddress(std::string& phone) {
    while(true) {
        if(standardString(phone).size() == 11
                && phone[0] == '+'
                && standardString(phone)[0] == '7') {
            break;
        }
        std::cout << "Invalid number format. Should be +7<10 digits>. Try again--> ";
        getline(std::cin, phone);
    }
    this->phone = phone;
    std::cout << "   enter the name of the contact--> ";
    getline(std::cin, this->name);
    std::cout << "New contact " << this->name << ", " << this->phone << ", added successfully.\n";
    return *this;
}

void Address::printAddress() {
    std::cout << this->name 
              << "\t" << this->phone 
              << "\n";
}

void Address::standardFields(std::string& searchString) {
    for(int i {0}; i < searchString.size(); ++i) {
        char symbol = searchString[i];
        if(std::isdigit(symbol)) {
            this->phone += symbol;
        } else if(symbol >= 'A' && symbol <= 'Z'
                  || symbol >= 'a' && symbol <= 'z') {
            this->name += std::tolower(symbol);
        }
    }
}

void Address::callAddress() {
    std::cout << "We call "  << this->name << " " << this->phone << ".\n";
    timer(5);
    std::cout << "Answer received. " << "\n";
    std::cout << "Speak... When finished, press the key ENTER-->" << "\n";
    //stopwatchForWindows();
    stopWatchForLinux();
    std::cout << "The conversation is over.\n";
}

void Address::smsAddress() {
    std::cout << "The message is sent to " << this->name << " " << this->phone << ".\n";
    timer(3);
    std::cout << "Message sent successfully.\n";
}
