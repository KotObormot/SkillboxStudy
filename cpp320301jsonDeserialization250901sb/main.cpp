#include <iostream>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"

struct Record {
    std::string name;
    std::string family;
    int age;
    bool married;
};

int main() {
    Record record;
    std::ifstream file("/home/itsme/skillbox/20250831sb322json-serialization/data/record.json");

    if(!file.is_open()) {
        std::cerr << "File not found.\n";
        return 1;
    }
     
    // 07:28 Запись поля в итоговую структуру 
    nlohmann::json dict;
    file >> dict;
    file.close();
    std::cout << dict["name"] << "\t" << dict["family"] << "\t" << dict["age"] << "\t" << std::boolalpha << dict["married"]  << "\n";    

    record.name = dict["name"];
    record.family = dict["family"];
    record.age = dict["age"];
    record.married = dict["married"];
    std::cout << record.name<< "\t" << record.family << "\t" << record.age << "\t" << std::boolalpha << record.married << "\n";
}