#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool catch_fish(std::vector<std::string>& river, std::vector<std::string>& basket, std::vector<int>& fishCount, const std::string& fish, int& rivCount) {
    bool isFishBiting {false};
    int i {0};
    while(!isFishBiting && i < river.size()) {
        auto rivIter = river.cbegin();
        if(!river[i].compare(fish)) {
            rivCount++;
            river.erase(rivIter + i);
            bool isFishInBasket {false};
            int j = 0;                
            while(j < basket.size() && !isFishInBasket) {
                if(!basket[j].compare(fish)) {
                    isFishInBasket = true;                            
                } else {
                    j++;
                }
            }                
            if(isFishInBasket) {
                fishCount[j]++;
            } else {
                basket.push_back(fish);
                fishCount.push_back(1);
            }                
            isFishBiting = true;
        } else {
            i++;
        }
    }
    return isFishBiting;    
}

int main() {
    std::vector<std::string> river;     // Fish in the river
    std::vector<std::string> basket;    // Fish in a basket
    std::vector<int> fishCount;     // The amount of each type of fish in the basket
    std::ifstream riv("../data/river200503.txt");   // 
    std::ofstream bask("../data/basket200503.txt");
    if(!riv.is_open() || !bask.is_open()) {
        std::cerr << "Error opening file!\n";
    } else {
        std::cout << "File opened.\n";
    }

    while(!riv.eof()) {
        std::string bufferR {""};
        std::getline(riv, bufferR);
        river.push_back(bufferR);
    }
    river.resize(river.size() - 1);

    char goOn {'+'};
    int rivCount = 0;
    while(!river.empty() && goOn == '+' ) {
        std::string fish {""};
        std::cout << "What kind of fish do you catch?--> ";
        std::cin >> fish;
        
        if(!catch_fish(river, basket, fishCount, fish, rivCount) /*== false*/) {
            std::cout << "You didn't catch anything. ";
        } else {
            std::cout << "Cool! You caught " << fish << ". ";
        }
        
        if(!river.empty()) {
            std::cout << "Do you want to continue? Click + --> ";
            std::cin >> goOn;
        } else {
            std::cout << "The fishing is over, all the fish have been caught.\n";
        }
    }
    
    std::cout << "A receipt for the caught fish is attached.\n";

    bask << "You have " << rivCount << " pcs. " << "fish in a basket, including: \n";
    for(int i = 0; i < basket.size(); ++i) {
        bask << fishCount[i] << " pcs. of " << basket[i] << "\n";
    }
    bask << "\nWe look forward to seeing you again.\n====================================\n";

    riv.close();
    bask.close();
}