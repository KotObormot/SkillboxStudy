#include <fstream>
#include <iostream>

int main() {
    std::ifstream textToView;
    std::string pathToText = "../data/Tom_Hanks.txt";
    //std::cout << "Specify the path to the file --> ";
    while(!textToView.is_open()) {
        //std::cin >> pathToText;
        textToView.open(pathToText/*, std::ios::binary*/);
        if (!textToView.is_open()) {
            std::cerr << "Error opening file! Please type the correct path --> ";
        } else {
            std::cout << "File opened.\n=============================\n";
        }
    }

    std::string buffer;
    while(!textToView.eof()) {
        buffer = "";
        std::getline(textToView, buffer);
        std::cout << buffer;
        std::cout << "\n";
    }
      
    std::cout << "\n====================================\n";
        
    textToView.close();
}