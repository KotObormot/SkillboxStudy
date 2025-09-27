#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits> // для std::numeric_limits
#include <vector>

struct Subscriber {
    std::string phone;
    std::string name;
};

Subscriber search_subscriber(std::string& search_string) {
    Subscriber subs {};    
    for(int i {0}; i < search_string.size(); ++i) {
        char symbol = search_string[i];
        if(std::isdigit(symbol)) {
            subs.phone += symbol;
        } else if(symbol >= 'A' && symbol <= 'Z'
                  || symbol >= 'a' && symbol <= 'z') {
            subs.name += std::tolower(symbol);
        }
    }

    return subs;
}

void save_book(const std::map<std::string, Subscriber>& book, const std::string& directory) {
    std::ofstream bk(directory + "book.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    int b_size = book.size();
    bk.write((char*)& b_size, sizeof(b_size));
    for(const auto& [phone_norm, subscriber] : book) {
        int len = phone_norm.length();
        bk.write((char*)& len, sizeof(len));
        bk.write(phone_norm.c_str(), len);
        len = subscriber.phone.length();
        bk.write((char*)& len, sizeof(len));
        bk.write(subscriber.phone.c_str(), len);
        len = subscriber.name.length();
        bk.write((char*)& len, sizeof(len));
        bk.write(subscriber.name.c_str(), len);
    }
    bk.close();
}

bool load_book(std::map<std::string, Subscriber>& book, const std::string& directory) {
    bool isBookNoOpen {true};
    std::ifstream bk(directory + "book.bin", std::ios::in | std::ios::binary);
    if(!bk.is_open()) {        
        return isBookNoOpen;
    } else {
        isBookNoOpen = false;
        while(true) {
            std::string phone_norm;
            Subscriber subscriber;
            int b_size {};
            bk.read((char*)& b_size, sizeof(b_size));
            for(int i = 0; i < b_size; ++i) {
                int len {};
                bk.read((char*)& len, sizeof(len));
                phone_norm.resize(len);
                bk.read((char*) phone_norm.c_str(), len);
                bk.read((char*)& len, sizeof(len));
                subscriber.phone.resize(len);
                bk.read((char*) subscriber.phone.c_str(), len);
                bk.read((char*)& len, sizeof(len));
                subscriber.name.resize(len);
                bk.read((char*) subscriber.name.c_str(), len);
                book[phone_norm] = subscriber;
            }
            if(bk.eof()) {
                break;
            }
        }
        bk.close();
    }
    std::cout << "\n";
    return isBookNoOpen;
}

void add_subscriber(std::map<std::string, Subscriber>& book, Subscriber subscriber = {"", ""}) {    
    if(subscriber.phone.size() == 0) {
        std::cout << "Add a subscriber: enter the phone number--> ";
        getline(std::cin, subscriber.phone);
    }
    if(subscriber.name.size() == 0) {
        std::cout << "   enter the name--> ";
        getline(std::cin, subscriber.name);
    }
    std::pair<std::string, Subscriber> theSubscriber(search_subscriber(subscriber.phone).phone, subscriber);    
    std::cout << "The subscriber " << subscriber.name << ", " << subscriber.phone << ", "
              << " added successfully.\n";
    book.insert(theSubscriber);
}

std::vector<std::map<std::string, Subscriber>::iterator> find_phone(std::map<std::string, Subscriber>& book, std::string phoneLooking) {
    std::vector<std::map<std::string, Subscriber>::iterator> iter_found {};
    std::map<std::string, Subscriber>::iterator itF {book.find(phoneLooking)};
    if(itF != book.end()) {
        iter_found.push_back(itF);
        std::cout << "Subscriber found:\n" << itF->second.name << "\t" << itF->second.phone << "\n";
    } else {
        std::cout << "Subscriber not found.\n";
    }
    return iter_found;    
}

std::vector<std::map<std::string, Subscriber>::iterator> find_name(std::map<std::string, Subscriber>& book, std::string nameLooking) {
    for(int i {0}; i < nameLooking.size(); ++i) {
        nameLooking[i] = std::tolower(nameLooking[i]);
    }
    std::vector<std::map<std::string, Subscriber>::iterator> iter_found {};
    for(std::map<std::string, Subscriber>::iterator it {book.begin()};
            it != book.end(); ++it) {
        std::string name = it->second.name;
        for(int i {0}; i < name.size(); ++i) {
            name[i] = std::tolower(name[i]);
        }
        if(name.find(nameLooking) == std::string::npos) {
            continue;
        } else {
            iter_found.push_back(it);
        }
    }
    if(iter_found.size() == 1) {
        std::cout << "Subscriber found:\n";
        std::cout << iter_found[0]->second.name << "\t" << iter_found[0]->second.phone << "\n";
    } else if(iter_found.size() > 1) {
        std::cout << "Subscribers found:\n";
        for(int i {0}; i < iter_found.size(); ++i) {
            std::cout << i << ") " << iter_found[i]->second.name << "\t" << iter_found[i]->second.phone << "\n";
        }
        std::cout << "\n";
    } else {
        std::cout << "Subscribers not found.\n";
    }
    return iter_found;
}

void delete_subscriber(std::map<std::string, Subscriber>& book, std::vector<std::map<std::string, Subscriber>::iterator>& iter_found) {
    std::map<std::string, Subscriber>::iterator it_deletable {};
    if(iter_found.size() > 1) {
        std::cout << "Specify the number of the subscriber being deleted--> ";
        int num_deletable {};                
        std::cin.clear();
        std::cin >> num_deletable;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while(num_deletable >= iter_found.size()) {
            std::cout << "You made a mistake. Try entering the number again--> ";                
            std::cin.clear();
            std::cin >> num_deletable;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        it_deletable = iter_found[num_deletable];
    } else {
        it_deletable = iter_found[0];
    }
    std::cout << "Confirm subscriber deleting " << it_deletable->second.name << ", " 
              << it_deletable->second.phone << ": (y / n)--> ";
    char choice {};
    std::cin.clear();
    std::cin >> choice;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    choice = std::tolower(choice);
    while(choice != 'y' && choice != 'n') {
        std::cout << "Don't make it up, just type Y or N --> ";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        choice = std::tolower(choice);
    }
    if(choice == 'y') {
        book.erase(it_deletable);
        std::cout << "The subscriber has been successfully removed.\n";
    } else {
        std::cout << "Well, as you wish. Deletion cancelled.\n";
    }
}

void print_book(const std::map<std::string, Subscriber>& phoneBook) {
    for(const auto& [key, subs] : phoneBook) {
        std::cout << subs.name << "\t" << subs.phone << "\n";
    }
}

char what_to_do_next(bool condition) {
    char action;
    if(condition) { // is found
        std::cout << "Specify the next action: e edit / - delete / c continue--> ";
        std::cin.clear();
        std::cin >> action;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        action = std::tolower(action);
        while(action != 'e' 
              && action != '-'
              && action != 'c') {
            std::cout << "Anyway, please specify the next action: e edit / - delete / c continue--> ";
            std::cin.clear();
            std::cin >> action;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            action = std::tolower(action);
        }
    } else { // isn't found
        std::cout << "Specify the next action: + add / c continue--> ";
        std::cin.clear();
        std::cin >> action;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        action = std::tolower(action);
        while(action != '+'
              && action != 'c') {
            std::cout << "Anyway, please specify the next action: + add / c continue--> ";
            std::cin.clear();
            std::cin >> action;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            action = std::tolower(action);
        }
    }
    return action;
}

void edit_subscriber(std::map<std::string, Subscriber>& book, std::vector<std::map<std::string, Subscriber>::iterator>& iter_found) {
    std::map<std::string, Subscriber>::iterator it_editable {};
    if(iter_found.size() > 1) {
        std::cout << "Specify the number of the subscriber being edited--> ";
        int num_editable {};                
        std::cin.clear();
        std::cin >> num_editable;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while(num_editable >= iter_found.size()) {
            std::cout << "You made a mistake. Try entering the number again--> ";                
            std::cin.clear();
            std::cin >> num_editable;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        it_editable = iter_found[num_editable];
    } else {
        it_editable = iter_found[0];
    }
    std::cout << "Confirm subscriber editing " << it_editable->second.name << ", " 
              << it_editable->second.phone << ": (y / n)--> ";
    char choice {};
    std::cin.clear();
    std::cin >> choice;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    choice = std::tolower(choice);
    while(choice != 'y' && choice != 'n') {
        std::cout << "Don't make it up, just type Y or N --> ";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        choice = std::tolower(choice);
    }
    if(choice == 'y') {
        Subscriber subscriber_editable;
        std::cout << "Enter new name--> ";
        getline(std::cin, subscriber_editable.name);
        it_editable->second.name = subscriber_editable.name;
        std::cout << "  and new phone--> ";
        getline(std::cin, subscriber_editable.phone);
        it_editable->second.phone = subscriber_editable.phone;
        std::cout << "Subscriber successfully edited:\n" 
                  << it_editable->second.name << "\t" << it_editable->second.phone << "\n";
    } else {
        std::cout << "Well, as you wish...\n";
    }
}

int main() {
    std::cout << "Hello!\n";
    std::map<std::string, Subscriber> phoneBook;

    std::cout << "Loading...\nSpecify the directory with the saved phone book --> ";
    std::string directory {/*/"../data/220601/"*/};
    std::cin >> directory;
    if(load_book(phoneBook,directory)) {
        std::cerr << std::setw(8) << "No saved phone book. Start a new phoone book.\n";
        add_subscriber(phoneBook);
    }
    char choice {};
    while(choice != 'q') {
        std::cout << "Enter the operating mode please:\n"
                  << "+ Add subscriber / "
                  << "s Search for a subscriber by phone number or name / "
                  << "p Print phone book / "
                  << "q End work"
                  << "--> ";                
        std::cin.clear();        
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        choice = std::tolower(choice);
        while(choice != '+'
                && choice != 'p'
                && choice != 's'
                && choice != 'q') {
            std::cout << "Finally, specify the direction already ( + / - / s / p ) or q to exit--> ";
            std::cin.clear();
            std::cin >> choice;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = std::tolower(choice);
        }
        if(choice == '+') {
            add_subscriber(phoneBook);         
        } else if(choice == 'p') {
            print_book(phoneBook);
        } else if(choice == 's') {
            std::string search_string;
            std::cout << "Enter the name or phone number of the subscriber you are looking for--> ";
            getline(std::cin, search_string);
            Subscriber subs = search_subscriber(search_string);
            if(subs.name.size()) {
                std::vector<std::map<std::string, Subscriber>::iterator> iter_found {find_name(phoneBook, subs.name)};
                bool nameFound {(bool)iter_found.size()};
                char action {what_to_do_next(nameFound)};
                if(action == 'e') {
                    edit_subscriber(phoneBook, iter_found);
                } else if(action == '+') {
                    add_subscriber(phoneBook, subs);
                } else if(action == '-') {
                    delete_subscriber(phoneBook, iter_found);
                } else {
                    continue;
                }
            }
            
            if(subs.phone.size()) {
                std::vector<std::map<std::string, Subscriber>::iterator> iter_found = find_phone(phoneBook, subs.phone);
                bool phonePhound {(bool)iter_found.size()};
                char action = what_to_do_next(phonePhound);
                if(action == '+') {
                    add_subscriber(phoneBook, subs);
                } else if(action == '-') {
                    delete_subscriber(phoneBook, iter_found);
                } else if(action == 'e') {
                    edit_subscriber(phoneBook, iter_found);
                } else {
                    continue;
                }
            } 
        }
        else {
            save_book(phoneBook, directory);
        }
    }

    return 0;
}