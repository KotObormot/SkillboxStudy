#include <iostream>
#include <map>
#include <string>

std::map<std::string, char>  splitting_string(const std::string& some_line) {
    std::map<std::string, char> split_string;
    for(size_t i {0}; i < some_line.size(); ++i) {
        std::string key {};
        char symbol {};
        if(some_line[i] >= 'A' && some_line[i] <= 'Z'
                  || some_line[i] >= 'a' && some_line[i] <= 'z') {
            symbol = std::tolower(some_line[i]);
            key = symbol + std::to_string(i);
        }
        split_string.emplace(key, symbol);
    }
    return split_string;
}

bool is_anagram (std::string& str_first, std::string& str_second) {
    bool isAnagram {true};
    std::map<std::string, char> map_first {splitting_string(str_first)};
    std::map<std::string, char> map_second {splitting_string(str_second)};
    if(map_first.size() != map_second.size()) {
        isAnagram = false;
        return isAnagram;
    }    
    std::map<std::string, char>::iterator it1 {map_first.begin()};
    std::map<std::string, char>::iterator it2 {map_second.begin()};
    while(it1 != map_first.end() && it2 != map_second.end()) {
        if(it1->second == it2->second) {
            ++it1;
            ++it2;
        } else {
            isAnagram = false;
            break;
        }
    }
    return isAnagram;
}

int main() {
    std::cout << "Enter the first line--> ";
    std::string str_first;
    getline(std::cin, str_first);

    std::cout << "Enter the second line--> ";
    std::string str_second;
    getline(std::cin, str_second);

    if(is_anagram(str_first, str_second)) {
        std::cout << "This is an anagram." << "\n";
    } else {
        std::cout << "This is not an anagram." << "\n";
    }
    return 0;

}