#include <fstream>
#include <iostream>

int main() {
    std::ifstream words;
    words.open("../data/words.txt");
    if (!words.is_open()) {
        std::cerr << "Error opening file!\n";
        return 1;
    } else {
        std::cout << "File opened.\n";
    }

    std::string wordToFind;
    std::cout << "What word/words are you looking for? --> ";
    std::cin >> wordToFind;
    
    int count = 0;
    while(!words.eof()) {
        std::string wordInWords = "";
        words >> wordInWords;
        if (wordToFind == wordInWords) {
            count++;
        }
    }
        
    if(count == 0) {
        std::cout << "There is no such word in the text.\n";
    } else if (count == 1) {
        std::cout << "The word occurs " << count << " time.\n";
    } else {
        std::cout << "The word occurs " << count << " times.\n";
    }

    words.close();
}