#include <string>
#include <iostream>

int main() {
    std::string residents[10];
    std::cout << "Hello user!\nI'm a directory for the residents of the house.\nEnter 10 residents' names.\n";
    for(int i = 0; i < 10; ++i) {
        std::cout << i << ": ";
        std::cin >> residents[i];
    }
    std::cout << "Ok. \nNow enter 3 numbers of the apartments you are interested in, and I will show you who lives in it.\n";
    int apartments[3];
    for(int j = 0; j < 3; ++j) {
        do {
            std::cout << j << ": ";
            std::cin >> apartments[j];
            if (apartments[j] > 9) {
                std::cout << "You are mistaken. Try again.\n";
            }
        }
        while(apartments[j] > 9);         
    }
    std::cout << "Ok.\nHere is a list of residents by apartment:\n";
    for(int j = 0; j < 3; ++j) {
        std::cout << apartments[j] << ":\t" << residents[apartments[j]] << ".\n";
    } 

    return 0;
}
