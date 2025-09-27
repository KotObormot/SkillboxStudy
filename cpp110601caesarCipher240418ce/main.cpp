#include <iostream>

char encrypt_caesar(char symbolOld, int shiftIn) {    
    /*std::cout << "shiftOut = " << shiftIn % 26 << "\n";*/
    char symbolNew/* = ((symbolOld >= 'A' && symbolOld <= 'Z') 
        || (symbolOld >= 'a' && symbolOld <= 'z')) ? (symbolOld + shiftIn % 26) : symbolOld*/;
    if (symbolOld >= 'A' && symbolOld <= 'Z') {
        if (symbolOld + shiftIn % 26 > 'Z') {
            symbolNew = symbolOld + shiftIn % 26 - 26; 
        } else {
            symbolNew = symbolOld + shiftIn % 26;
        }
    }
    else if (symbolOld >= 'a' && symbolOld <= 'z') {
        if (symbolOld + shiftIn % 26 > 'z') {
            symbolNew = symbolOld + shiftIn % 26 - 26; 
        } else {
            symbolNew = symbolOld + shiftIn % 26;
        }
    } else {
        symbolNew = symbolOld;
    }   
        
    return symbolNew;
}

int main() {

    std::cout << "Enter text: ";
    std::string text;
    std::getline(std::cin, text);
    std::cout << "Enter code: ";
    int code;
    std::cin >> code;
    std::string textNew = "";
    for (int i = 0; i < text.length(); ++i) {
        textNew += encrypt_caesar(text[i], code);
    }

    std::cout << textNew << "\n";

    return 0;
}