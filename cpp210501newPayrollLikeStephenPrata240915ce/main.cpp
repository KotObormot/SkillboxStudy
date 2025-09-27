#include <fstream>
#include <iostream>
//#include <vector>
#include <string>
//#include <cstring>
//#include <cstdlib>
#include <limits> // для std::numeric_limits
#include <iomanip>
#define DEBUG false

struct Recipients {
    //std::string name {""};
    //std::string surname {""};
    char name[20];
    std::string date;
    double salary;
    //char absaz {'\n'};
};

inline void eatline() {
    while(std::cin.get() != '\n') {
        #if DEBUG
            std::cout << "!BLA! ";
        #endif
        continue;
    }
}

double handling_invalid_input() {
    while (true) { // Цикл, пока пользователь не введет допустимые данные
        std::cout << " and amount-->  ";
        double x{0};
        std::cin >> x;
        // Проверяем на неудачное извлечение
        if (std::cin.fail()) { // предыдущее извлечение не удалось?        
            // да, давайте разберемся с ошибкой
            std::cin.clear(); // возвращаем нас в "нормальный" режим работы
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');     // и удаляем неверные входные данные
            std::cout << "Oops, that input is invalid.  Please try again: ";
        }   
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');; // удаляем любые посторонние входные данные
            return x;
        }
    }   
}  

bool isDateFormat(std::string& date) {
    bool isDateCorrect {true};
    if(date.find('.') == std::string::npos) {
        isDateCorrect = false;
        return isDateCorrect;
    }
    int dd {0};    
    try {
        dd = stoi(date.substr(0, date.find('.')));
    } catch (const std::invalid_argument& e) {
        isDateCorrect = false;        
        return isDateCorrect;
    } catch (const std::out_of_range& e) {
        isDateCorrect = false;        
        return isDateCorrect;
    }
    if(date.find('.') == 1) {
        date.insert(0, "0");
    } else if (date.find('.') > 2){
        isDateCorrect = false;
        return isDateCorrect;
    }
    if(dd > 31 || dd < 1) {
        isDateCorrect = false;
        return isDateCorrect;
    }

    int mm {0};
    if(date.find('.', 3) == std::string::npos) {
            isDateCorrect = false;
            #if DEBUG
                std::cerr << "Not found\n";
            #endif
            return isDateCorrect;
    } else {
        try {
            mm = stoi(date.substr(3, date.find('.', 3) - 3));
        } catch(const std::invalid_argument& e) {
            isDateCorrect = false;
            return isDateCorrect;
        } catch(const std::out_of_range& e) {
            isDateCorrect = false;
            return isDateCorrect;
        }
        if(mm > 12 || mm < 1) {
            isDateCorrect = false;
            return isDateCorrect;
        } else if(mm > 0 && mm < 10 && date.find('.', 3) == 4) {
            date.insert(3, "0");
        }
    }

    if((date.substr(6)).size() == 2) {
        date.insert(6, "20");
    } else if((date.substr(6)).size() != 2 && (date.substr(6)).size() != 4) {
        isDateCorrect = false;
        return isDateCorrect;
    }
    int yyyy {0};
    try {
        yyyy = stoi((date.substr(6)));
    } catch(const std::invalid_argument& e) {
        isDateCorrect = false;
        return isDateCorrect;
    } catch(const std::out_of_range& e) {
        isDateCorrect = false;
        return isDateCorrect;
    }
    bool leap = (yyyy % 400 == 0) || ((yyyy % 4 == 0) && (yyyy % 100 != 0));
    if(((mm == 2) && ((leap && dd > 29) || (!leap && dd > 28)))
        || ((mm == 4 || mm == 6 || mm == 9 || mm == 11) && dd == 31)) {
            isDateCorrect = false;
            return isDateCorrect;
    }
    return isDateCorrect;
}

std::string get_correct_date(/*std::string& date*/) {
    std::string date {""};
    std::cout << "Enter the date in the format dd.mm.yyyy--> ";
    std::cin >> date;
    while(!isDateFormat(date)) {
        std::cout << "Enter correct date please -->  ";
        std::cin >> date;
    }
    return date;
}

void add_recipients(const std::string& path_to_file, Recipients& recipient, const char& choice) {
    std::ofstream file;
    if(choice == '+') {
        file.open(path_to_file, std::ios::out | std::ios::app | std::ios::binary);
    } else if(choice == 'n') {        
        file.open(path_to_file, std::ios::out | std::ios::binary | std::ios::trunc);
    }
    std::cout << "Enter name or blank line to quit--> ";
    eatline();
    std::cin.get(recipient.name, 20);
    while(recipient.name[0] != '\0') {
        std::cout << " Enter payment details - date and amount:\n";
        recipient.date = get_correct_date();
        recipient.salary = handling_invalid_input();
        #if DEBUG
            std::cout << "input check: " <<  recipient.name << " " << recipient.date << " " << recipient.salary << "\n";
        #endif
        file.write((char*)& recipient, sizeof(recipient));
        std::cout << "Enter name or blank line to quit--> ";
        std::cin.get(recipient.name, 20);
    }
    file.close();
}

void print_recipients(const std::string& path_to_file, Recipients& recipient) {
    std::ifstream file(path_to_file, std::ios::in | std::ios::binary);
    if(!file.is_open()) {
        std::cerr << "Accounting statement is missing. Please fill it out. ";
        add_recipients(path_to_file, recipient, 'n');
        return;
    } else {
        while(file.read((char*)& recipient, sizeof(recipient))) {
            std::cout.setf(std::ios::showpoint);
            std::cout.setf(std::ios::fixed);
            std::cout.precision(2);
            std::cout.width(20);
            std::cout << recipient.name << ": ";
            std::cout.width(12);
            std::cout << recipient.date;
            std::cout.width(10); 
            std::cout << recipient.salary << "\n";
        }
        file.close();
    }
}

int main() {
    Recipients recipient;
    std::string path_to_file {};
    #if DEBUG
        path_to_file = "../data/payroll.bin";
    #endif
    std::cout << "Enter the path to file the statement--> ";
    std::cin >> path_to_file;

    char choice {};
    while(choice != 'q') {
        std::cout << "Enter the operating mode please:\n";
        std::cout << "+ Add recipient to payroll / n Create a new statement / < Output the statement / q End work--> ";
        #if DEBUG 
            std::cout << std::cin.get() << "\n";
        #endif
        std::cin.clear();
        #if DEBUG 
            std::cout << std::cin.get() << "\n";
        #endif
        std::cin >> choice;
        if(choice == '+' || choice == 'n') {
            add_recipients(path_to_file, recipient, choice);
        } else if (choice == '<') {
            print_recipients(path_to_file, recipient);
        }
    }
    return 0;
}
