#include "phone.h"

void Phone::addAddressInBook() {
    Address address;
    address.addAddress();
    std::string firstTmp {address.getPhone()};
    std::pair<std::string, Address> newContact(standardString(firstTmp), address);
    phoneBook.insert(newContact);
}

void Phone::addAddressInBook(std::string& phone) {
    Address address;
    address.addAddress(phone);
    std::string first {address.getPhone()};
    std::pair<std::string, Address> newContact(standardString(first), address);
    phoneBook.insert(newContact);
}

void Phone::saveBook() {
    std::ofstream bk("./data/book.bin", std::ios::out | std::ios::trunc | std::ios::binary);
    int b_size = phoneBook.size();
    bk.write((char*)& b_size, sizeof(b_size));
    for(const auto& [first, second] : phoneBook) {
        int len = first.length();
        bk.write((char*)& len, sizeof(len));
        bk.write(first.c_str(), len);
        Address tmp = second;
        std::string phn = tmp.getPhone();
        len = phn.length();
        bk.write((char*)& len, sizeof(len));
        bk.write(phn.c_str(), len);
        std::string nmn = tmp.getName();
        len = nmn.length();
        bk.write((char*)& len, sizeof(len));
        bk.write(nmn.c_str(), len);
    }
    bk.close();
}

bool Phone::loadBook() {   
    bool isBookNoOpen {true};
    std::ifstream bk("./data/book.bin", std::ios::in | std::ios::binary);
    if(!bk.is_open()) {        
        return isBookNoOpen;        
    } else {
        isBookNoOpen = false;
        while(true) {
            if(bk.eof()) {
                break;
            }
            std::string phone_norm;
            Address subscriber;
            int b_size {};
            bk.read((char*)& b_size, sizeof(b_size));
            for(int i {0}; i < b_size; ++i) {
                int len {};
                bk.read((char*)& len, sizeof(len));
                phone_norm.resize(len);
                bk.read((char*) phone_norm.c_str(), len);
                bk.read((char*)& len, sizeof(len));
                std::string phTemp {};
                phTemp.resize(len);
                bk.read((char*) phTemp.c_str(), len);
                subscriber.setPhone(phTemp);
                bk.read((char*)& len, sizeof(len));
                std::string nmTmp {};
                nmTmp.resize(len);
                bk.read((char*) nmTmp.c_str(), len);
                subscriber.setName(nmTmp);
                std::pair<std::string, Address> anySubs(phone_norm, subscriber);
                phoneBook.insert(anySubs);
            }
        }
        bk.close();
    }
    return isBookNoOpen;
}

void Phone::show() {
    for(const auto& [first, second] : phoneBook) {
        Address printedAddress {second};
        printedAddress.printAddress();
    }
}

std::vector<std::map<std::string, Address>::iterator> Phone::findPhone(std::string& phoneLooking) { //phone number search method
    std::vector<std::map<std::string, Address>::iterator> iter_found {};
    std::map<std::string, Address>::iterator itF {phoneBook.find(phoneLooking)};
    if(itF != phoneBook.end()) {
        iter_found.push_back(itF);
    }
    return iter_found;    //returns a vector of iterators of found numbers: 0 - nothing found, > 0 - 1 or more found
}

std::vector<std::map<std::string, Address>::iterator> Phone::findName(std::string& nameLooking) {
    std::vector<std::map<std::string, Address>::iterator> iter_found {};
    for(std::map<std::string, Address>::iterator itF {phoneBook.begin()};
            itF != phoneBook.end(); ++itF) {
        std::string name = itF->second.getName();
        if(standardString(name).find(nameLooking) == std::string::npos) {
            continue;
        } else {
            iter_found.push_back(itF);
        }
    }    
    return iter_found;
}

void Phone::call() {
    std::string searchString;
    std::cout << "Enter the name or phone number (in the format +7<10 digits>) of the person you are calling--> ";
    getline(std::cin, searchString);
    
    Address searchedAddress;
    Address foundAddress;

    searchedAddress.standardFields(searchString);

    if((bool)searchedAddress.getPhone().size()) {
        std::string sercheadPhone {searchedAddress.getPhone()}; // new
        std::vector<std::map<std::string, Address>::iterator> iterFound {findPhone(/*searchedAddress.phone*/sercheadPhone)};
        if((bool)iterFound.size()) {
            foundAddress.setName(iterFound[0]->second.getName());
            foundAddress.setPhone(iterFound[0]->second.getPhone());
            foundAddress.callAddress();
        } else {
            std::cout << "No contact. ";
            searchedAddress.callAddress();
            addAddressInBook(searchString);
        }

    } else if((bool)searchedAddress.getName().size()) {
        std::string searchedName {searchedAddress.getName()};
        std::vector<std::map<std::string, Address>::iterator> iterFound {/*newBook.*/findName(searchedName)};
        if(iterFound.size() == 1) {
            foundAddress.setName(iterFound[0]->second.getName());
            foundAddress.setPhone(iterFound[0]->second.getPhone());
            foundAddress.callAddress();
        } else if(iterFound.size() > 1) {
            std::cout << "Contacts detected:\n";
            for(int i {0}; i < iterFound.size(); ++i) {
                std::cout << i << ") " << iterFound[i]->second.getName() << "\t" << iterFound[i]->second.getPhone() << "\n";
            }
            std::cout << "\n";
            std::map<std::string, Address>::iterator itCalled {};
            std::cout << "Specify the contact to be called--> ";
            int contactCalled {};
            std::cin.clear();
            std::cin >> contactCalled;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while(contactCalled >= iterFound.size()) {
                std::cout << "You made a mistake. Try again--> ";                
                std::cin.clear();
                std::cin >> contactCalled;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            itCalled = iterFound[contactCalled];
            foundAddress.setName(itCalled->second.getName());
            foundAddress.setPhone(itCalled->second.getPhone());
            foundAddress.callAddress();
        } else {
            std::cout << "No contact. ";
            return;
        }
    }    
}

void Phone::sms() {
    std::string searchString;
    std::cout << "Enter the name or phone number (in the format +7<10 digits>) of the person you are sending the message to--> ";
    getline(std::cin, searchString);
    
    Address searchedAddress;
    Address foundAddress;

    searchedAddress.standardFields(searchString);

    if((bool)searchedAddress.getPhone().size()) {
        std::string sercheadPhone {searchedAddress.getPhone()}; // new
        std::vector<std::map<std::string, Address>::iterator> iterFound {findPhone(sercheadPhone)};
        if((bool)iterFound.size()) {
            foundAddress.setName(iterFound[0]->second.getName());
            foundAddress.setPhone(iterFound[0]->second.getPhone());
            foundAddress.smsAddress();
        } else {
            std::cout << "No contact. ";
            searchedAddress.smsAddress();
            addAddressInBook(searchString);
        }
    } else if((bool)searchedAddress.getName().size()) {
        std::string searchedName {searchedAddress.getName()};    
        std::vector<std::map<std::string, Address>::iterator> iterFound {findName(searchedName)};
        if(iterFound.size() == 1) {
            foundAddress.setName(iterFound[0]->second.getName());
            foundAddress.setPhone(iterFound[0]->second.getPhone());
            foundAddress.smsAddress();
        } else if(iterFound.size() > 1) {
            std::cout << "Contacts detected:\n";
            for(int i {0}; i < iterFound.size(); ++i) {
                std::cout << i << ") " << iterFound[i]->second.getName() << "\t" << iterFound[i]->second.getPhone() << "\n";
            }
            std::cout << "\n";
            std::map<std::string, Address>::iterator itCalled {};
            std::cout << "Specify the contact to whom to send the message--> ";
            int contactCalled {};
            std::cin.clear();
            std::cin >> contactCalled;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while(contactCalled >= iterFound.size()) {
                std::cout << "You made a mistake. Try again--> ";                
                std::cin.clear();
                std::cin >> contactCalled;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            itCalled = iterFound[contactCalled];
            foundAddress.setName(itCalled->second.getName());
            foundAddress.setPhone(itCalled->second.getPhone());
            foundAddress.smsAddress();
        } else {
            std::cout << "No contact. ";
            return;
        }
    }
}