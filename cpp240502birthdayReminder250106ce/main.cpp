#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits> // для std::numeric_limits
#include <vector>
#include <ctime>

#define DEBUG false

struct Birtsday {
    bool isDateCorrect;
    int day;
    int month;
    int year;
};

struct Friend {
    Birtsday birthday;
    std::string name;
};

Birtsday isDateFormat(std::string& date) {
    Birtsday date_correct;
    date_correct.isDateCorrect = true;
    bool& isDateCorrect = date_correct.isDateCorrect;
    if(date.find('.') == std::string::npos) {
        isDateCorrect = false;
        return date_correct;
    }
    date_correct.day = 0;
    int& dd {date_correct.day};   
    try {
        dd = stoi(date.substr(0, date.find('.')));
    } catch (const std::invalid_argument& e) {
        isDateCorrect = false;        
        return date_correct;
    } catch (const std::out_of_range& e) {
        isDateCorrect = false;        
        return date_correct;
    }
    if(date.find('.') == 1) {
        date.insert(0, "0");
    } else if (date.find('.') > 2){
        isDateCorrect = false;
        return date_correct;
    }
    if(dd > 31 || dd < 1) {
        isDateCorrect = false;
        return date_correct;
    }        

    date_correct.month = 0;
    int& mm {date_correct.month};
    if(date.find('.', 3) == std::string::npos) {
            isDateCorrect = false;
            return date_correct;
    } else {
        try {
            mm = stoi(date.substr(3, date.find('.', 3) - 3));
        } catch(const std::invalid_argument& e) {
            isDateCorrect = false;
            return date_correct;
        } catch(const std::out_of_range& e) {
            isDateCorrect = false;
            return date_correct;
        }
        if(mm > 12 || mm < 1) {
            isDateCorrect = false;
            return date_correct;
        } else if(mm > 0 && mm < 10 && date.find('.', 3) == 4) {
            date.insert(3, "0");
        }
    }
    if((date.substr(6)).size() == 2) {
        date.insert(6, "20");
    } else if((date.substr(6)).size() != 2 && (date.substr(6)).size() != 4) {
        isDateCorrect = false;
        return date_correct;
    }
    date_correct.year = 0;
    int& yyyy {date_correct.year};
    try {
        yyyy = stoi((date.substr(6)));
    } catch(const std::invalid_argument& e) {
        isDateCorrect = false;
        return date_correct;
    } catch(const std::out_of_range& e) {
        isDateCorrect = false;
        return date_correct;
    }
    bool leap = (yyyy % 400 == 0) || ((yyyy % 4 == 0) && (yyyy % 100 != 0));
    if(((mm == 2) && ((leap && dd > 29) || (!leap && dd > 28)))
        || ((mm == 4 || mm == 6 || mm == 9 || mm == 11) && dd == 31)) {
            isDateCorrect = false;
            return date_correct;
    }
    return date_correct;
}

void save_list(const std::map<int, Friend>& friends_list, const std::string& directory) {
    std::ofstream frndslst(directory + "friends.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    size_t list_size = friends_list.size();
    frndslst.write((char*)& list_size, sizeof(list_size));
    for(const auto& [first, second] : friends_list) {
        frndslst.write((char*)& first, sizeof(first));
        frndslst.write((char*)& second.birthday.isDateCorrect, sizeof(second.birthday.isDateCorrect));
        frndslst.write((char*)& second.birthday.day, sizeof(second.birthday.day));
        frndslst.write((char*)& second.birthday.month, sizeof(second.birthday.month));
        frndslst.write((char*)& second.birthday.year, sizeof(second.birthday.year));
        int len = second.name.length();
        frndslst.write((char*)& len, sizeof(len));
        frndslst.write(second.name.c_str(), len);
    }
    frndslst.close();
}

bool load_list(std::map<int, Friend>& friens_list, const std::string& directory) {
    bool isFileNoOpen {true};
    std::ifstream frndslst(directory + "friends.bin", std::ios::in | std::ios::binary);
    if(!frndslst.is_open()) {        
        return isFileNoOpen; // true
    } else {
        isFileNoOpen = false;
        while(true) {
            size_t list_size {};
            frndslst.read((char*)& list_size, sizeof(list_size));
            for(int i = 0; i < list_size; ++i) {
                int first;
                Friend second;
                frndslst.read((char*)& first, sizeof(first));
                frndslst.read((char*)& second.birthday.isDateCorrect, sizeof(second.birthday.isDateCorrect));
                frndslst.read((char*)& second.birthday.day, sizeof(second.birthday.day));
                frndslst.read((char*)& second.birthday.month, sizeof(second.birthday.month));
                frndslst.read((char*)& second.birthday.year, sizeof(second.birthday.year));
                int len {};
                frndslst.read((char*)& len, sizeof(len));
                second.name.resize(len);
                frndslst.read((char*) second.name.c_str(), len);                
                std::pair<int, Friend> brtsday_new(first, second);
                friens_list.insert(brtsday_new);
            }
            if(frndslst.eof()) {
                break;
            }
        }
        frndslst.close();
    }
    std::cout << "\n";
    return isFileNoOpen;
}

void add_friend(std::map<int, Friend>& list) {
    int first = list.size();
    Friend second {};
    std::cout << "Add a friend: enter his/her name or end to exit--> ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');            
    std::getline(std::cin, second.name);
    std::string anysymbols {};
        for(int i {0}; i < second.name.size(); ++i) {
            anysymbols += std::tolower(second.name[i]);
        }
    while(anysymbols != "end") {
        if(anysymbols == "end") {
            break;
        } else{
            std::cout << " and her/his birtsday (with format dd.mm.yyyy))--> ";
            std::string brtsdy_get {};
            std::cin >> brtsdy_get;
            while(!isDateFormat(brtsdy_get).isDateCorrect) {
                std::cout << "Enter correct date please--> ";
                std::cin >> brtsdy_get;
            }
            second.birthday = isDateFormat(brtsdy_get);
            ++first;
            std::pair<int, Friend> any_frnd(first, second);
            list.insert(any_frnd);
            std::cout << "Your friend " << first << ") " << second.name << ", " << second.birthday.year 
                      << "/" << second.birthday.month 
                      << "/" << second.birthday.day 
                      << ", " << " added successfully.\n";
            std::cout << "Add a friend: enter her(his) name or end to exit--> ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');            
            std::getline(std::cin, second.name);
            anysymbols = {};
            for(int i {0}; i < second.name.size(); ++i) {
                anysymbols += std::tolower(second.name[i]);
            }
        }
    }
}

std::vector<std::map<int, Friend>::iterator> find_birtsday(std::map<int, Friend>& list, std::time_t& birtsdayLooking) {
    std::vector<std::map<int, Friend>::iterator> iter_found {};
    for(std::map<int, Friend>::iterator it {list.begin()};
            it != list.end(); ++it) {
        int day_b = it->second.birthday.day;
        int month_b = it->second.birthday.month; 

        std::tm* date_local = localtime(&birtsdayLooking);
        int day_d = date_local->tm_mday;
        int month_d = date_local->tm_mon + 1;

        if((day_d == day_b) && (month_d == month_b)) {
            iter_found.push_back(it);
        } else {
            continue;
        } 
    }
    return iter_found;
}

#if DEBUG
void print_list(const std::map<int, Friend>& list) {
    for(const auto& [first, second] : list) {
        std::cout << first << ") " 
                << second.name << "\t" 
                << second.birthday.year << "/" 
                << second.birthday.month << "/" 
                << second.birthday.day << ".\n";
    }
}
#endif

void today(std::map<int, Friend>& list) {
    std::time_t today_looking = std::time(nullptr);
    std::vector<std::map<int, Friend>::iterator> iter_found {find_birtsday(list, today_looking)};
    std::tm* date_local = localtime(&today_looking);        
    int year_d = date_local->tm_year + 1900;
    if(iter_found.size() == 1) {
        std::cout << "Friend found:\n";
        int year_b = iter_found[0]->second.birthday.year;
        std::cout << iter_found[0]->second.name << "\t" << (year_d - year_b) << " years.\n";
    } else if(iter_found.size() > 1) {
        std::cout << "Friends found:\n";
        for(int i {0}; i < iter_found.size(); ++i) {
            int year_b = iter_found[i]->second.birthday.year;
            std::cout << iter_found[i]->second.name << "\t" << (year_d - year_b) << " years.\n";
        }
        std::cout << "\n";
    } else {
        std::cout << "Friends not found.\n";
    }
}

void this_week(std::map<int, Friend>& list) {
    bool isNotFound {true};
    std::time_t t = std::time(nullptr);
    for(int i {0}; i < 7 * 24 * 3600; i += 24 * 3600) {
        std::time_t t_looking = t + i;
        std::tm* date_local = localtime(&t_looking);
        int year_d = date_local->tm_year + 1900;
        std::vector<std::map<int, Friend>::iterator> iter_found = find_birtsday(list, t_looking);
        if(iter_found.size() == 1) {
            isNotFound = false;
            int year_b = iter_found[0]->second.birthday.year;
            std::cout << std::put_time(date_local, "%B, %d: *") << std::setw(25) << std::left << iter_found[0]->second.name << "\t" << (year_d - year_b) << " years.\n";
        } else if(iter_found.size() > 1) {
            isNotFound = false;
            std::cout << std::put_time(date_local, "%B, %d") << ":\n";
            for(int i {0}; i < iter_found.size(); ++i) {
                int year_b = iter_found[i]->second.birthday.year;
                std::cout << std::setw(15) << std::right << "* " << std::setw(25) << std::left << iter_found[i]->second.name<< (year_d - year_b) << " years.\n";
            }
        } 
    }
    if(isNotFound) {
        std::cout << "Not found.\n";
    }
}

int main() {
    std::cout << "Hello!\n";
    std::map<int, Friend> friends_list;

    std::cout << "Loading...\nSpecify the directory with the saved friends list--> ";
    std::string directory {/*"../data/240502-1/"*/};
    std::cin >> directory;
    if(load_list(friends_list, directory)) {
        std::cerr << std::setw(8) << "No saved friends list. Start a new friends list.\n";
        add_friend(friends_list);
    }
    std::cout << "Today is my friends birthday:\n";
    today(friends_list);

    char choice {};
    while(choice != 'q') {
        std::cout << "Enter the operating mode please:\n"
                  << "+ Add friend / "
                  << "w Search for upcoming birthdays this week / "
#if DEBUG
                  << "p Print friends list / "
#endif
                  << "q End work"
                  << "--> ";                
        std::cin.clear();        
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        choice = std::tolower(choice);
        while(choice != '+'
                && choice != 'w'
                && choice != 'p'
                && choice != 'q') {
            std::cout << "Finally, specify the direction already ( + / - / s / p ) or q to exit--> ";
            std::cin.clear();
            std::cin >> choice;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = std::tolower(choice);
        }
        if(choice == '+') {
            add_friend(friends_list);         
        } 
#if DEBUG         
        else if(choice == 'p') {
            print_list(friends_list);
        }
#endif   
        else if(choice == 'w') {
            this_week(friends_list);        
        } 
        else {
            save_list(friends_list, directory);
        }
    }

    return 0;
}