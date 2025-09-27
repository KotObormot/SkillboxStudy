#include <fstream>
#include <iostream>
#include <string>

bool isDateFormat(std::string& date) {

    bool isDateCorrect {true};
    if(date.find('.') == std::string::npos) {
        isDateCorrect = false;
        return isDateCorrect;
    }
    int dd = stoi(date.substr(0, date.find('.')));
    if(date.find('.') <= 2) {
        if(dd > 0 && dd < 10) {
            date.insert(0, "0");
        } else if(dd > 31) {
            isDateCorrect = false;
        }        
    } else {
        isDateCorrect = false;
    }
    
    int mm;    
    if(date.find('.', 3) == std::string::npos) {
            isDateCorrect = false;
            return isDateCorrect;
    } else {
        mm = stoi(date.substr(3, date.find('.', 3)));
        if(mm > 0 && mm < 10) {
            date.insert(3, "0");
        } else if(mm > 12) {
            isDateCorrect = false;
        }
    }

    if((date.substr(6)).size() == 2) {
        date.insert(6, "20");
    } else if((date.substr(6)).size() != 2 && (date.substr(6)).size() != 4) {
        isDateCorrect = false;
    }
    
    int yyyy = stoi((date.substr(6)));
    bool leap = (yyyy % 400 == 0) || ((yyyy % 4 == 0) && (yyyy % 100 != 0));
    if((leap && mm == 2 && (dd == 30 || dd == 31))
        || (!leap && mm == 2 && (dd == 29 || dd == 30 || dd == 31))
        || ((mm == 4 || mm == 6 || mm == 9 || mm == 11) && dd == 31)) {
            isDateCorrect = false;
    }

    return isDateCorrect;
}

int main() {
    std::ofstream payRoll("../data/payroll200501.txt", std::ios::app);
    if(!payRoll.is_open()) {
        std::cerr << "Error opening file!\n";
    } else {
        std::cout << "File opened.\n";
    }

    std::string stName = {""};
    std::string stSurname = {""};
    double stFee = 0;
    std::string pmntDate = {""};
    bool gameOver {true};
    
    while(gameOver) {         
        std::cout << "Enter payment details: first name, last name, date and amount--> ";
        std::cin >> stName >>  stSurname >> pmntDate >> stFee;
        while(!isDateFormat(pmntDate)) {
            std::cout << "Enter correct date --> ";
            std::cin >> pmntDate;
        }

        std::cout << "To end input, enter 0--> ";
        std::cin >> gameOver;

        payRoll.setf(std::ios::showpoint); 
        payRoll.setf(std::ios::fixed); 
        payRoll.precision(2); 

        payRoll.width(20);
        payRoll << stName;
        payRoll.width(20);
        payRoll << stSurname;
        payRoll.width(11);
        payRoll << pmntDate;
        payRoll.width(10);
        payRoll << stFee;
        payRoll.width(5);
        payRoll << "\n";
        
    }

    payRoll.close();    
}