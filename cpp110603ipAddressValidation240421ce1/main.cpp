#include <iostream>

/*The function returns TRUE if the octet is OK*/
bool isOctetCorrect(std::string someString) {
    bool isCorrect = false;
    if(someString.length() == 1) {               
        if(someString[0] >= '0' && someString[0] <= '9') {            
            isCorrect = true;
        }
    } else if(someString.length() == 2) {
        if(someString[0] > '0' && someString[0] <= '9') {
            if(someString[1] >= '0' && someString[0] <= '9') {
                isCorrect = true;
            }
        }
    } else if(someString.length() == 3) {
        if(someString[0] == '1') {
            if(someString[1] >= '0' && someString[0] <= '9') {
                if(someString[2] >= '0' && someString[2] <= '9') {
                    isCorrect = true;
                }
            } 
        } else if(someString[0] == '2') {
            if(someString[1] >= '0' && someString[0] <= '5') {
               if(someString[2] >= '0' && someString[2] <= '5') {
                    isCorrect = true;
                } 
            }
        }
    } else {
        isCorrect = false;
    }

    return isCorrect;
}

/*The function extracts each octet, sends it for verification and returns the result*/

bool isEachOctetCorrect(std::string someString, int numberOfPoints, char dotSymbol) {
    bool crrntOctetCrrct = false;
    int startPosition = 0;
    int dotPosition = 0;
    std::string currentOctet = "";
    std::string lastOctet = ""; 
    int dotCounter = 0;

    for(int i = 0; i < someString.length(); ++i) {
        if(someString[i] == dotSymbol) {
            ++dotCounter;
            dotPosition = i;
            for(int j = startPosition; j < dotPosition; ++j) {            
                currentOctet = someString.substr(startPosition, dotPosition - startPosition);
            }
            if(isOctetCorrect(currentOctet)) {
                crrntOctetCrrct = true;
                startPosition = dotPosition + 1;
                currentOctet = "";
            } else {
                crrntOctetCrrct = false;
                break;
            }
        }        
    }

    if(crrntOctetCrrct) {
        lastOctet = someString.substr(dotPosition + 1, someString.length() - 1 - dotPosition);
        if(isOctetCorrect(lastOctet)) {
            crrntOctetCrrct = true; 
        } else {
            crrntOctetCrrct = false;
        }         
    } else {
        crrntOctetCrrct = false;
    }

    if(dotCounter != numberOfPoints) {
        crrntOctetCrrct = false;
    } 
    return crrntOctetCrrct;
}

int main() {
    std::cout << "Enter ip-address please: ";
    std::string ipAddress;
    std::cin >> ipAddress;

    if(isEachOctetCorrect(ipAddress, 3, '.')) {
        std::cout << "Valid.\n";
    } else {
        std::cout << "Invalid.\n";
    }
    
    return 0;
}
