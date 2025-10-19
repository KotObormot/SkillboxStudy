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
    std::cout << "-->";
    std::cin >> record.name >> record.family >> record.age >> record.married;

    std::ofstream file("/home/itsme/skillbox/20250831sb322json-serialization/record.json");
//    file << "{" << "\"name\": \"" << record.name << "\", \"family\": \"" << record.family << "\"" << "}" << std::endl;
 
/*
    nlohmann::json dict;        // json объект    
    dict["name"] = record.name;
    dict["family"] = record.family;
    dict["age"] = record.age;
    dict["married"] = record.married;
*/  
    //  The same thing, but even simpler:
    nlohmann::json dict = {
        {"name", record.name}
        , {"family", record.family}
        , {"age", record.age}
        , {"married", record.married}
    };

    file << dict;
    file.close();

    // 06:41 Парсинг кода из строковых констант 
    std::ofstream file1("record1.json");
    nlohmann::json dict1 = "{ \"name\" : \"Vladislav\", \"family\" : \"Surkov\" }"_json;
    file1 << dict1;
    file1.close();
}