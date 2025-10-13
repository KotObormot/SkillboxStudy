#include <iomanip>
#include "forest.h"

Forest::Forest(): root(nullptr) {}

Forest::~Forest() {
    delete root;
}

void Forest::create() {
    root = new Branch(nullptr, "None");

    size_t numTrees(NUMBER_OF_TREES); // 5 trees
    std::cout << "There are "<< numTrees << " trees in the elven village.\n";
    for (size_t i(0); i < numTrees; ++i) {

        Branch* tree(new Branch(root, "None"));
        root->addChild(tree);

        size_t numLargeBranches(randomNumber(NUMBER_OF_LARGE_BRANCHES_MIN, NUMBER_OF_LARGE_BRANCHES_MAX));
        std::cout << "Tree # " << i << " has " << numLargeBranches << " large branches.\n";
        for (size_t j(0); j < numLargeBranches; ++j) {
            std::cout << "\t" << i << "." << j << ": What is the elf's name?--> ";
            std::string name;
            getline(std::cin, name);

            Branch* largeBranch(new Branch(tree, name));
            tree->addChild(largeBranch);

            size_t numMiddleBranches(randomNumber(NUMBER_OF_MIDDLE_BRANCHES_MIN, NUMBER_OF_MIDDLE_BRANCHES_MAX));
            std::cout << "\tLarge branch # " << j << " has " << numMiddleBranches << " middle branches.\n";
            for (size_t k(0); k < numMiddleBranches; ++k) {
                std::cout << "\t\t" << i << "." << j << "." << k << ": What is the elf's name?--> ";
                getline(std::cin, name);

                Branch* middleBranch(new Branch(largeBranch, name));
                largeBranch->addChild(middleBranch);
            }
        }
    }
}

void Forest::search(const std::string& name, Branch* node, bool& found, std::vector<std::string>& neighbordNames) {
    if (!node || found) return;

    if (node->elfName == name && getLowerName(node->elfName) != "none") {
        found = true;

        if(node->children.size() != 0) {
            for(size_t i(0); i < node->children.size(); ++i) {
                if(getLowerName(node->children[i]->elfName) != "none") {
                    neighbordNames.push_back(node->children[i]->elfName);
                }
            }
        } else {
            if(getLowerName(node->parent->elfName) != "none") {
                neighbordNames.push_back(node->parent->elfName);
            }
 
            for(size_t i(0); i < node->parent->children.size(); ++i) {
                if((getLowerName(node->parent->children[i]->elfName) != "none")
                        && (getLowerName(node->parent->children[i]->elfName) != getLowerName(name))) {
                    neighbordNames.push_back(node->parent->children[i]->elfName);
                }
            }
        }        
        
        return;
    }

    for(size_t i(0); i < node->children.size(); ++i) {
        search(name, node->children[i], found, neighbordNames);
    }
}

void Forest::findNeighbors(const std::string& name) {
    bool found = false;
    std::vector<std::string> neighborsNames;
    
    search(name, root, found, neighborsNames);

    if (found) {
        if (!neighborsNames.empty()) {
            std::cout << "Neighbors of " << name << ": " << neighborsNames.size() << "\n";
            for(size_t i(0); i < neighborsNames.size(); ++i) {
                std::cout << "\t" << i << ") " << neighborsNames[i] << "\n";
            }
            std::cout << "\n";
        } else {
            std::cout << name << " has no neighbors.\n";
        }
    } else {
        std::cout << "Elf " << name << " not found." << "\n";
    }
}

void Forest::print() {
       for(size_t i(0); i < root->children.size(); ++i) {
        std::cout <<"Tree # " << i << ")";
        root->children[i]->print();
        std::cout << "\n";
        for(size_t j(0); j < root->children[i]->children.size(); ++j) {
            std::cout <<"\tLarge branch # " << j << "]";
            root->children[i]->children[j]->print();
            std::cout << "\n";
            for(size_t k(0); k < root->children[i]->children[j]->children.size(); ++k) {
                std::cout <<"\t\tMiddle branch # " << k << ":";
                root->children[i]->children[j]->children[k]->print();
                std::cout << "\n";
            }
        }
    } 
}
