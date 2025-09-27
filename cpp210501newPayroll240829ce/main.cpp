#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <limits> // для std::numeric_limits
#include <iomanip>
#define DEBUG false

struct Recipients {
    std::string name {""};
    //char name[50];
    std::string surname {""};
    std::string date {""};
    double salary {0};
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
            std::cerr << "Not found\n";
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

std::string get_correct_date() {
    std::string date {""};
    std::cout << "Enter the date in the format dd.mm.yyyy--> ";
    std::cin >> date;
    while(!isDateFormat(date)) {
        std::cout << "Enter correct date please -->  ";
        std::cin >> date;
    }
    return date;
//    if(isDateFormat(date)) {
//        std::cout << "Correct date: " << date << "\n";
//    } else {
//        std::cerr << "Incorrect date.\n";
//    }
}

void add_recipients(const std::string& path_to_file, const char& choice) {
    std::vector<Recipients> recipient;    
    std::string name {""};
    std::string surname {""};
    std::string date {""};
    double salary {0};
    
    std::cout << "Enter name or ESC to quit--> ";
    eatline();
    std::cin >> name;
    while((int)name[0] != 27) {
        #if DEBUG
            std::cout << (int)name[0] << " !!\n";
        #endif
        std::cout << " Enter surname--> ";
        std::cin >> surname;
        std::cout << " Enter payment details - date and amount:\n";
        date = get_correct_date();
        salary = handling_invalid_input();
        #if DEBUG
            std::cout << "input check: " << name << " " << surname << " " << date << " " << salary << "\n";
        #endif
        recipient.push_back({name, surname, date, salary});
        std::cout << "Enter name or ESC to quit--> ";
        std::cin >> name;
    }
    #if DEBUG
        for(int i = 0; i < std::size(recipient); ++i) {
            std::cout << recipient[i].name << " " << recipient[i].surname << " " << recipient[i].date << " " << recipient[i].salary << "\n";
        }
    #endif
    std::ofstream file;
    if(choice == '+') {
        file.open(path_to_file, std::ios::out | std::ios::app | std::ios::binary);
    } else if(choice == 'n') {        
        file.open(path_to_file, std::ios::out | std::ios::binary | std::ios::trunc);
    }
    for(int i = 0; i < std::size(recipient); ++i) {
        int name_len = recipient[i].name.length();
        int surname_len = recipient[i].surname.length();
        int date_len = recipient[i].date.length();
        file.write((char*)& name_len, sizeof(name_len));
        file.write(recipient[i].name.c_str(), name_len);
        file.write((char*)& surname_len, sizeof(surname_len));
        file.write(recipient[i].surname.c_str(), surname_len);
        file.write((char*)& date_len, sizeof(date_len));
        file.write(recipient[i].date.c_str(), date_len);
        file.write((char*)& recipient[i].salary, sizeof(recipient[i].salary));
    }    
    file.close();
}

void print_recipients(const std::string& path_to_file) {
    std::vector<Recipients> recipiet;
    std::string name {""};
    std::string surname {""};
    std::string date {""};
    double salary {0};
    std::ifstream file(path_to_file, std::ios::in | std::ios::binary);
    if(!file.is_open()) {
        std::cerr << "Accounting statement is missing. Please fill it out. ";
        add_recipients(path_to_file, 'n');
        return;
    } else {
        while(!file.eof()) {            
            int len;
            file.read((char*)&len, sizeof(len));
            name.resize(len);
            file.read((char*) name.c_str(), len);
            
            file.read((char*)& len, sizeof(len));
            surname.resize(len);
            file.read((char*) surname.c_str(), len);
            
            file.read((char*)& len, sizeof(len));
            date.resize(len);
            file.read((char*) date.c_str(), len);

            file.read((char*)& salary, sizeof(salary));

            recipiet.push_back({name, surname, date, salary});
        }
        file.close();
    }
    recipiet.resize(recipiet.size() - 1);
    
    for(int i = 0; i < std::size(recipiet); ++i) {
            std::cout.setf(std::ios::showpoint);
            std::cout.setf(std::ios::fixed);
            std::cout.precision(2);
            std::cout.width(20);
            std::cout << recipiet[i].name + " " + recipiet[i].surname << ": ";
            std::cout.width(12);
            std::cout << recipiet[i].date;
            std::cout.width(10); 
            std::cout << recipiet[i].salary << "\n";
    }
}

int main() {

    #if DEBUG
        std::cout.setf(std::ios::boolalpha); // для булевых переменных    
    #endif
    
    std::string path_to_file {"../data/payroll.bin"};
    //std::cout << "Enter the path to file the statement--> ";
    //std::cin >> path_to_file;

    char choice {};
    
    while(choice != 'q') {
        std::cout << "Enter the operating mode please:\n";
        std::cout << "+ Add recipient to payroll / n Create a new statement / < Output the statement / q End work--> ";
        #if DEBUG 
            std::cout << std::cin.get() << "\n";
        #endif
        std::cin.clear();
        #if DEBUG 
            std::cout << std::cin.get() << " !\n";
        #endif
        std::cin >> choice;
        if(choice == '+' || choice == 'n') {
            add_recipients(path_to_file, choice);
        } else if (choice == '<') {
            print_recipients(path_to_file);            
        }
    }
    return 0;
}