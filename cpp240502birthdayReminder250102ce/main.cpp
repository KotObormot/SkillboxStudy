#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits> // для std::numeric_limits
#include <vector>
#include <ctime>

#define DEBUG true

struct Friend {
    std::tm birtsday;
    std::string name;
};

void save_list(const std::map<int, Friend>& friends_list, const std::string& directory) {
    std::ofstream frndslst(directory + "friends.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    size_t list_size = friends_list.size();
    frndslst.write((char*)& list_size, sizeof(list_size));
    for(const auto& [first, second] : friends_list) {
        frndslst.write((char*)& first, sizeof(first));
        frndslst.write((char*)& second.birtsday, sizeof(second.birtsday));
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
                frndslst.read((char*)& second.birtsday, sizeof(second.birtsday));
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
    std::cout << "Add a friend: enter her(his) name or end to exit--> ";
    std::cin.clear();
    std::getline(std::cin, second.name);
    std::string anysymbols {};
        for(int i {0}; i < second.name.size(); ++i) {
            anysymbols += std::tolower(second.name[i]);
        }
    while(anysymbols != "end") {
        if(anysymbols == "end") {
            break;
        } else{
            std::tm brtsdy_get {};
            do {
                std::cin.clear();
                std::cout << " and her/his birtsday with format dd.mm.yyyy--> ";
                std::cin.clear();
                std::cin >> std::get_time(&brtsdy_get, "%d.%m.%Y");
                if(!std::cin.fail()) {
                    break;
                }
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            while(true);
            second.birtsday = brtsdy_get;
#if DEBUG
            std::cout << second.birtsday.tm_mday << "."
                    << second.birtsday.tm_mon + 1 << "."
                    << second.birtsday.tm_year + 1900 << " "
                    << second.birtsday.tm_hour << ":"
                    << second.birtsday.tm_min << ":"
                    << second.birtsday.tm_sec << ", "
                    << second.birtsday.tm_wday + 1 << " - day of the week, "
                    << second.birtsday.tm_yday << "th day since the beginning of the year, "
                    << second.birtsday.tm_isdst << " - daylight saving time transition, "
                    //<< brtsdy_get.tm_zone << " - time zone, "
                    //<< brtsdy_get.tm_gmtoff << "- gmtoff"
                    << "\n";
#endif
            ++first;
            std::pair<int, Friend> any_frnd(first, second);
            list.insert(any_frnd);
            const std::time_t t_brtsd = std::mktime(&second.birtsday);
            std::cout << "Your friend " << second.name << ", " << std::put_time(std::localtime(&t_brtsd), "%d.%m.%Y") << ", "
                    << " added successfully.\n";

            std::cout << "Add a friend: enter her(his) name--> ";
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

std::vector<std::map<int, Friend>::iterator> find_birtsday(std::map<int, Friend>& list, std::tm* birtsdayLooking) {
    std::vector<std::map<int, Friend>::iterator> iter_found {};
    for(std::map<int, Friend>::iterator it {list.begin()}; it != list.end(); ++it) {
        int day_b = it->second.birtsday.tm_mday;
        int month_b = it->second.birtsday.tm_mon + 1;
        int day_d = birtsdayLooking->tm_mday;
        int month_d = birtsdayLooking->tm_mon + 1;
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
        std::tm t = second.birtsday;
        const std::time_t t_brtsd = std::mktime(&t);
        std::cout << first << ") " << second.name 
                  << "\t" << std::put_time(&second.birtsday, "%d.%m.%Y")
                  << "\t" << std::put_time(std::localtime(&t_brtsd), "%Y/%m/%d")
                  << "\n";
    }
}
#endif

void today(std::map<int, Friend>& list) {
    std::time_t today_looking = std::time(nullptr);
    std::tm* date_local = localtime(&today_looking);
    std::vector<std::map<int, Friend>::iterator> iter_found {find_birtsday(list, date_local)};
    int year_d = date_local->tm_year + 1900;
    if(iter_found.size() == 1) {
        std::cout << "Friend found:\n";
        int year_b = iter_found[0]->second.birtsday.tm_year + 1900;
        std::cout << iter_found[0]->second.name << "\t" << (year_d - year_b) << " years.\n";
    } else if(iter_found.size() > 1) {
        std::cout << "Friends found:\n";
        for(int i {0}; i < iter_found.size(); ++i) {
            int year_b = iter_found[i]->second.birtsday.tm_year + 1900;
            std::cout << i << ") " << iter_found[i]->second.name << "\t" << (year_d - year_b) << " years.\n";
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
        std::vector<std::map<int, Friend>::iterator> iter_found = find_birtsday(list, date_local);
        if(iter_found.size() == 1) {
            isNotFound = false;
            int year_b = iter_found[0]->second.birtsday.tm_year + 1900;
            std::cout << std::put_time(date_local, "%B, %d: *") << std::setw(25) << std::left 
                      << iter_found[0]->second.name << "\t" 
                      << (year_d - year_b) << " years.\n";
        } else if(iter_found.size() > 1) {
            isNotFound = false;
            std::cout << std::put_time(date_local, "%B, %d") << ":\n";
            for(int i {0}; i < iter_found.size(); ++i) {
                int year_b = iter_found[i]->second.birtsday.tm_year + 1900;
                std::cout << std::setw(15) << std::right << "* " << std::setw(25) << std::left 
                          << iter_found[i]->second.name<< (year_d - year_b) 
                          << " years.\n";
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
    std::string directory {};
    //std::cin >> directory;
    directory = "../data/240502/";
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
        } else {
            save_list(friends_list, directory);
        }
    }

    return 0;
}