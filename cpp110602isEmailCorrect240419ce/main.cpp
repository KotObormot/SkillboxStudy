#include <iostream>

/*The function returns the position of the given character in the text
 or 0 if it is not there, or there is more than 1, 
 or it is in the first or last position in the text*/
int atSymbolPosition(std::string someText, char someSymbol) {
    int atSmblPstn = 0;
    int atSmblCount = 0;
    for(int i = 0; atSmblCount <= 1 && i < someText.length(); ++i) {
        if(someText[i] == someSymbol) {
            atSmblPstn = i;
            ++atSmblCount;
        }
    }
    return ((atSmblCount == 1) && (atSmblPstn != someText.length() - 1)) ? atSmblPstn : 0;
}

/*The function returns TRUE if the string being checked contains only valid characters
 from the dictionary string*/
bool isCorrectSymbols(std::string stringDictionary, std::string stringTest) { 
    bool isCorrectAllSymbols = true;
    for(int i = 0; isCorrectAllSymbols && i < stringTest.length(); ++i) {
        bool isMatch = false;
        for(int j = 0; !isMatch && j < stringDictionary.length(); ++j) {
            if(stringTest[i] != stringDictionary[j]) {
                continue;
            } else {
                isMatch = true; 
            }
        }
        isCorrectAllSymbols = isMatch;
    }
    return isCorrectAllSymbols;   
}

/*The function returns TRUE if the text has a point
 neither at the beginning nor at the end, 
 and if there are no two points in a row*/
bool isPointsCorrect(std::string someText, char someChar) {
    bool isPntCrrct = false;
    if(someText[0] != someChar && someText[someText.length() - 1] != someChar) {
        isPntCrrct = true;
    }
    for(int i = 1; isPntCrrct && i < someText.length(); ++i) {
        if(someText[i - 1] == someChar && someText[i] == someChar) {
            isPntCrrct = false;
        }
    }
    return isPntCrrct;
} 

/*there is at least one point*/
bool isAtLeastOnePoint(std::string someText, char someChar) {
    bool isOnePoint = false;
    for(int i = 0; !isOnePoint && i < someText.length(); ++i) {
        if(someText[i] == someChar) {
            isOnePoint = true;
        }
    }
    return isOnePoint;
}

/*Function to check the left side - username*/
bool isUsernameCorrect(std::string someText) {
    std::string stringDictionaryLeft = "!#$%&'*+-/=?^_`{|}~.0123456789ABCDEFGYIJKLMNOPQRSTVUWXYZabcdefghijklmnopqrstuvwxyz";
    bool isUsrnmCrrct = false;
    if((bool)atSymbolPosition(someText, '@')){
        std::string userName = someText.substr(0, atSymbolPosition(someText, '@'));
        if(userName.length() > 0 && userName.length() <= 64) {
            if(isCorrectSymbols(stringDictionaryLeft, userName)) {
                if(isPointsCorrect(userName, '.')) {
                    isUsrnmCrrct = true;
                }
            }
        }
    }
    return isUsrnmCrrct;
}

/*Function for checking the right side - domain*/
bool isDomainCorrect(std::string someText) {
    std::string stringDictionaryRight = "-.0123456789ABCDEFGYIJKLMNOPQRSTVUWXYZabcdefghijklmnopqrstuvwxyz";
    bool isDmnCrrct = false;
    if((bool)atSymbolPosition(someText, '@')) {
        std::string domainName = someText.substr(atSymbolPosition(someText, '@') + 1, someText.length() - atSymbolPosition(someText, '@'));
        if(domainName.length() > 0 && domainName.length() <= 63) {
            if(isAtLeastOnePoint(domainName, '.')) {
                if(isCorrectSymbols(stringDictionaryRight, domainName)) {
                    if(isPointsCorrect(domainName, '.')) {
                        isDmnCrrct = true;
                    }
                }
            }
        }
    }
    return isDmnCrrct;
}

void emailIsCorrect() {
    std::cout << "Yes, E-mail is correct.\n";
}

void emailIsNotCorrect() {
    std::cout << "No, E-mail is not correct.\n";
}


int main() {
    std::cout << "Enter e-mail: ";
    std::string email;
    std::cin >> email;
        
    if((bool)atSymbolPosition(email, '@') && isUsernameCorrect(email) && isDomainCorrect(email)) {
            emailIsCorrect(); 
        } else {
            emailIsNotCorrect();
        }

    return 0;
}