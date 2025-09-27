#include "store.h"

Store::Store() {
    std::ifstream storeFile;
    
    storeFile.exceptions(std::fstream::badbit | std::fstream::failbit);
    try {
        std::cout << "Attempt to open the store.\n";
        storeFile.open("store1.json");
        std::cout << "The store is open.\n";
    }
    catch(const std::ifstream::failure& ex) {
        std::cerr << ex.what() << " with code " << ex.code() << ": "
                  << "File \"store.json\" not found.\n";
        return;
    }

    json storeJ(json::parse(storeFile));
    storeFile.close();

//    std::cout << storeJ.dump(4) << "\n";
    store = storeJ;

    for(auto& [article, number] : store) {
        if(number < 0) {
            std::cout << "The " << article << " is out of store.\n";
            number = 0;
        }
    }
}

void Store::print() {
    std::cout << "\n========== PRODUCTS IN THE STORE: ==============\n";
    for(const auto& [article, number] : store) {
        std::cout << article << ":\t" << number << "\n";
    }
    std::cout << "=================================================\n";
}

std::map<std::string, int>::iterator Store::checkProduct(std::string& product) {
    bool notSuccess(true);
    std::map<std::string, int>::iterator it(store.begin());
    for(it; it != store.end(); ++it) {

        std::string article = normString(it->first);

        if(article.find(product) == std::string::npos) {
            continue;            
        } else {
            std::cout << it->first << " found! " /*<< it->second*/ << "\n";
            notSuccess = false;
            break;
        }
    }
    if(notSuccess) {
        throw std::string {product + " not found!"};
    }
    return it;
}

void Store::checkNumber(std::map<std::string, int>::iterator it, int number) {
    if(it->second < number) {
        throw std::string {"But " +  it->first + " is not enough!"};
    } else {
        std::cout << it->first << " sold!\n";
        it->second -= number;
    }
} 

Store::~Store() {
    json storeJ = store;
    std::ofstream storeFile("store1.json");
    storeFile << storeJ.dump(4);
    storeFile.close();
}