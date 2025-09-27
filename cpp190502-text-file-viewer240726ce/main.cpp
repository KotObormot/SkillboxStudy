#include <fstream>
#include <iostream>

int main() {
    std::ifstream textToView;
    std::string pathToText = "../data/Tom_Hanks.txt";
    //std::cout << "Specify the path to the file --> ";
    while(!textToView.is_open()) {
        //std::cin >> pathToText;
        textToView.open(pathToText, std::ios::binary);
        if (!textToView.is_open()) {
            std::cerr << "Error opening file! Please type the correct path --> ";
        } else {
            std::cout << "File opened.\n=============================\n";
        }
    }
        
    int count = 0;

    while(!textToView.eof()) {
        textToView.seekg(count, std::ios::beg);
        char buffer[20] = {};
        textToView.read(buffer, 20);
        buffer[19] = 0;
        std::cout << buffer;
        count += textToView.gcount() - 1;
    }

    std::cout << "\n=============================\n";
        
    textToView.close();
}