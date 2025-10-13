#include "forest.h"

void Forest::createForest() {
    std::srand(std::time(nullptr));
    for(size_t i(0); i < NUMBER_OF_TREES; ++i) {
        std::cout << "Tree # " << i << ":\n";
        std::vector<std::vector<Branch>> someTree;
        size_t branchesNumberLargeTMP {std::rand() % 3 + 3};
        std::cout << branchesNumberLargeTMP << " large branches.\n";

        for(size_t j(0); j < branchesNumberLargeTMP; ++j) {
            std::vector<Branch> someLargeBranch;
            std::cout << "Large branch # " << j << ": ";            
            size_t branchesNumberMiddleTMP {std::rand() % 2 + 2};
            std::cout << branchesNumberMiddleTMP << " middle branches.\n";
            Branch largeBranch;
            std::cout << " Elf on the large branch: " ;
            largeBranch.setName();
            someLargeBranch.push_back({largeBranch});

            for(size_t k(1); k <= branchesNumberMiddleTMP; ++k) {
                std::cout << "Middle branch # " << k << ": ";
                Branch middleBranch;
                middleBranch.setName();
                someLargeBranch.push_back({middleBranch});                
            }

            someTree.push_back(someLargeBranch);
        }

        trees.push_back(someTree);
    }
}

void Forest::print() {
    std::cout << "Trees = " << trees.size() << "\n";

    for(size_t i(0); i < trees.size(); ++i) {        
        std::cout << "\nTree # " << i << ": " << trees[i].size() << " large branches:\n";

        for(size_t j(0); j < trees[i].size(); ++j) {
            std::cout << "\tLarge branch # " << j << ": " << "\n";
            std::cout << "\t  House on the large branch: "; 
            std::cout << trees[i][j][0].getName() << "\n";
            std::cout << "\t  Middle branches = " << trees[i][j].size() - 1 << "\n";
            for(size_t k(1); k < trees[i][j].size(); ++k) {
                std::cout << "\t\tMiddle branch # " << k - 1 << ": " << trees[i][j][k].getName() << "\n";
            }
        }
    }
    std::cout << "\n";
}

void Forest::searchForElf(const std::string& name) {
    bool isFound(false);
    size_t x, y, z;
    x = y = z = 0;
    for(size_t i(0); i < trees.size(); ++i) {
        for(size_t j(0); j < trees[i].size(); ++j) {
            for(size_t k(0); k < trees[i][j].size(); ++k) {
                
                if(trees[i][j][k].getName().find(name) == std::string::npos) {
                    continue;
                } else {
                    x = i;
                    y = j;
                    z = k;
                    isFound = true;
                    break;
                }                
            }
        }
    }
    if(isFound) {        
        size_t neighborCounter {0};
        size_t i {0};
        while(true) {
            if(i == trees[x][y].size()) {
                break;
            }
            if(trees[x][y][i].getName() != trees[x][y][z].getName()
                    && trees[x][y][i].getLowerName() != "none") {
                std::cout << "Neighbor # " << neighborCounter << ": " << trees[x][y][i].getName() << ",\n";
                ++neighborCounter;
            }
            ++i;
        }
        if(neighborCounter) {
            std::cout << "\n---------------------------\nTOTAL " << neighborCounter << " neighbors."
                      << "\n===========================\n";
        } else {
            std::cout << "No neighbors.\n";
        }
    } else {
        std::cout << "Not found.\n";
    }
}

