#include "basket.h"

void Basket::add() {
    std::cout << "Article--> ";
    std::string a (correctCommandInput());

    std::map<std::string, int>::iterator it{};
    while(true) {
        try {
            it = store.checkProduct(a);
            break;
        }
        catch(const std::string& error_message) {
            std::cout << error_message << "\n";
            std::cout << "Article--> ";
            a = correctCommandInput();
        }
    }

    std::cout << "Number ";
    int n;
    while(true) {
        try {
            n = handlingIntInput();
            if(n < 0) {
                throw n;
            } else {
                break;
            }
        }
        catch(int n) {
            std::cout << "The number must be >=0. Try again";
        }
    }

    try {
        store.checkNumber(it, n);
    }
    catch(const std::string& error_message) {
        std::cout << error_message << "\n";
        return;
    }

    std::map<std::string, int>::iterator itBasket(basket.begin());
    bool alreadyInBasket(false);
    for(itBasket; itBasket != basket.end(); ++itBasket) {
        if(itBasket->first.find(it->first) != std::string::npos) {
            alreadyInBasket = true;
            break;
        }
    }
    if(alreadyInBasket) {
        basket[itBasket->first] += n;
    } else {
        basket.insert({it->first, n});
    }
}

void Basket::remove() {
    std::cout << "Article--> ";
    std::string a (correctCommandInput());

    std::map<std::string, int>::iterator it{};
    bool find(false);
    for(it = basket.begin(); it != basket.end(); ++it) {
        std::string article(normString(it->first));
        if(article.find(a) != std::string::npos) {
            find = true;
            break;
        } 
    }
    
    if(find) {
        std::cout << it->first << " Found.\n";
        std::cout << "Number";
        int n;
        while(true) {
            try {
                n = handlingIntInput();
                if(n < 0) {
                    throw n;
                } else {
                    break;
                }
            }
            catch(int n) {
                std::cout << "The number must be >=0. Try again";
            }
        }

        if(it->second < n) {
            std::cout << "Error. You cannot delete more than you have.";
            return;
        } else {
            if(it->second > n) {
                it->second -= n;
            } else {
                basket.erase(it->first);
            }
        }
    } else {
        std::cout << a << " is not in the basket.\n";
    }
}

void Basket::print() {
    std::cout << "\n--------- PRODUCTS IN THE BASKET: --------------\n";
    for(auto const& [article, number] : basket) {
        std::cout << article << ":\t" << number << "\n";
    }
    std::cout << "-------------------------------------------------\n";
}

void Basket::printStore() {
    store.print();
}