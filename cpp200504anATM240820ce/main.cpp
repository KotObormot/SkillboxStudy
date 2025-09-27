#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <limits> // для std::numeric_limits

int total_sum(const std::vector<int>& nominal, const std::vector<int>& banknote) {
    int sum {0};
    for(int i = 0; i < nominal.size(); ++i) {
        sum += nominal[i] * banknote[i];
    }
    return sum;
}

int banknotes(const std::vector<int>& banknote) {
    int total_count {0};
    for(int i = 0; i < banknote.size(); ++i) {
        total_count += banknote[i];
    }
    return total_count;
}

void console_output(const std::vector<int>& nominal, const std::vector<int>& banknote) {
    std::cout << "\t! Cash at ATM\n----------------------\n";
    for(int i = 0; i < nominal.size(); ++i) {
        std::cout.width(9);
        std::cout << nominal[i];
        std::cout.width(6);
        std::cout << banknote[i] << "\n";
    }
    std::cout << "\n----------------------\n";
    std::cout.width(9);
    std::cout << total_sum(nominal, banknote);
    std::cout.width(6);
    std::cout << banknotes(banknote) << "\n";
    return;
}

void read_file(const std::string& path, std::vector<int>& nominal, std::vector<int>& banknote) {
    std::ifstream atm(path, std::ios::binary);
    if(!atm.is_open()) {
        std::cerr << "\t!! Error opening file! ATM is not ready.\n";
        return;
    } else {
        std::cout << "\t! File opened. ATM is on.\n";
    }
    while(!atm.eof()) {
        int bufferN {0};
        int bufferB {0};
        atm >> bufferN >> bufferB;
        nominal.push_back(bufferN);
        banknote.push_back(bufferB);        
    }
    nominal.resize(nominal.size() - 1);
    banknote.resize(banknote.size() - 1);
    atm.close();
    return;    
}

void write_file(const std::string& path, std::vector<int>& nominal, std::vector<int>& banknote) {
    std::ofstream atm(path, std::ios::binary);
    if(!atm.is_open()) {
        std::cerr << "\t!! Error opening file! ATM is not ready.\n";
        return;
    } else {
        std::cout << "\t! File opened. The ATM is turned off.\n";
    }
    for(int i = 0; i < nominal.size(); ++i) {
        atm.width(6);
        atm << nominal[i];
        atm.width(6);
        atm << banknote[i] << "\n";
    }
    atm.close();
    return;
}

bool isNmnlStnd(const int& deposN) {
    bool isCrrct {false};
    std::vector<int> nStndrt {100, 200, 500, 1000, 2000, 5000};
    int i = 0;
    while(i < nStndrt.size() && !isCrrct) {
        if(nStndrt[i] == deposN) {
            isCrrct = true;
        } else {
            i++;
        }
    }
    return isCrrct;
}

void bubble_sort_function(std::vector<int>& nominal, std::vector<int>& banknote) {
    bool isSearchOver {true};
    int finPos = nominal.size();
    while(isSearchOver) {
        isSearchOver = false;
        for(int i = 0; i + 1 < finPos; i++) {
            if(nominal[i] < nominal[i+1]) {
                std::swap(nominal[i], nominal[i + 1]);
                std::swap(banknote[i], banknote[i + 1]);
                isSearchOver = true;
            }
        }
        finPos--;
    }
    return;
}

int handling_invalid_input() {
    while (true) { // Цикл, пока пользователь не введет допустимые данные
        std::cout << "->  ";
        int x{0};
        std::cin >> x;
        // Проверяем на неудачное извлечение
        if (std::cin.fail()) { // предыдущее извлечение не удалось?        
            // да, давайте разберемся с ошибкой
            std::cin.clear(); // возвращаем нас в "нормальный" режим работы
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');     // и удаляем неверные входные данные
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }   
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');; // удаляем любые посторонние входные данные
            return x;
        }
    }   
}   

void deposit_cash(std::vector<int>& nominal, std::vector<int>& banknote) {
    const int deposB_max {1000};
    int deposB_sum = banknotes(banknote);
    int deposN;
    int deposB;
    std::cout << "Enter the denomination -";
    deposN = handling_invalid_input();
    std::cout << " and number of banknotes to be deposited(no more than " << (deposB_max - deposB_sum) << " banknotes) -";
    deposB = handling_invalid_input();
    while(!isNmnlStnd(deposN)) {
        std::cout << "Please enter the correct denomination -";
        deposN = handling_invalid_input();
    }    
    bool isNmnl {false};
    int i = 0;
    while(i < nominal.size() && !isNmnl) {
        if(nominal[i] == deposN) {
            isNmnl = true;
        } else {
            i++;
        }
    }
    if(deposB_sum + deposB > deposB_max) {
        std::cout << "\t! You can deposit " << deposN * (deposB_max - deposB_sum) << " rubles in " << deposN << " ruble notes in the amount of ";
        std::cout << (deposB_max - deposB_sum) << " notes. Take back the " << (deposB_sum + deposB - deposB_max) << " notes that were not accepted.\n";
        deposB = deposB_max - deposB_sum;
    } else {
        std::cout << "\t! You deposited " << (deposN * deposB) << " rubles in " << deposN << " ruble notes in the amount of ";
        std::cout << deposB << " notes. \n";
    }
    if(isNmnl) {
        banknote[i] += deposB;
    } else {
        nominal.push_back(deposN);
        banknote.push_back(deposB);
    }
    bubble_sort_function(nominal, banknote);
    return;
}

void withdraw_cash(std::vector<int>& nominal, std::vector<int>& banknote) {
    if(nominal.empty() || banknote.empty() || total_sum(nominal, banknote) == 0 || banknotes(banknote) == 0) {
        std::cout << "\t! ATM is empty. Cash needs to be deposited.\n";
        return;
    }
    std::cout << "Enter the required amount of cash with an accuracy of 100 rubles -";
    int reqAmount {0};
    reqAmount = handling_invalid_input();
    while(reqAmount % 100 != 0) {
        std::cout << "Input error. Please enter a number that is a multiple of 100 -";
        reqAmount = handling_invalid_input();
    }
    while(reqAmount > total_sum(nominal, banknote)) {
        std::cout << "\t! Amount too large!\nPlease enter a smaller amount -";
        reqAmount = handling_invalid_input();
    }
    int rA = reqAmount;
    
    std::vector<int> reqNmnl;
    std::vector<int> reqBnknt;    
    for(int j = 0; j < nominal.size(); ++j) {
        int reqB = reqAmount / nominal[j];
        if(reqB <= banknote[j]) {
            reqNmnl.push_back(nominal[j]);
            reqBnknt.push_back(reqB);
            reqAmount %= nominal[j];
            banknote[j] -= reqB;
        } else {
            reqNmnl.push_back(nominal[j]);
            reqBnknt.push_back(banknote[j]);
            reqAmount -= nominal[j] * banknote[j];
            banknote[j] = 0;
        }
    }
    std::cout << "\t! You have been given " << total_sum(reqNmnl, reqBnknt) << " rubles in the following denominations: \n";
    for(int i = 0; i < reqNmnl.size(); ++i) {
        if(reqBnknt[i] != 0) {
            std::cout << "\t> denomination " << reqNmnl[i] << " rubles - " << reqBnknt[i] << "  pieces" "\n";
        }        
    }
    if(total_sum(reqNmnl, reqBnknt) < rA) {
        std::cout << "\t! It is not possible to issue the required amount. Come tomorrow for the remaining " << (rA - total_sum(reqNmnl, reqBnknt)) << " rubles.\n";
    }
    std::cout << "\n";
    return;
}

int main() {
    std::string path {"../data/bank200504.bin"};
    std::vector<int> nominal;
    std::vector<int> banknote;
    read_file(path, nominal, banknote);
    std::cout.setf(std::ios::boolalpha);
    if(nominal.empty() || banknote.empty() || total_sum(nominal, banknote) == 0 || banknotes(banknote) == 0) {
        std::cout << "\t! ATM is empty. Cash needs to be deposited.\n";
        deposit_cash(nominal, banknote);
    }
    char choice {};    
    while(choice != 'q') {
        std::cout << "\t! Enter the operating mode:\n";
        std::cout << "+ deposit cash / - withdraw cash / < show balance / q end work--> ";
        std::cin >> choice;        
        if(choice == '+') {
            deposit_cash(nominal, banknote);            
        } else if(choice == '-') {
            withdraw_cash(nominal, banknote);            
        } else if(choice == '<') {
            console_output(nominal, banknote);            
        } 
    }
    write_file(path, nominal, banknote);
    return 0;
}