#include <iostream>
#include "enterprise.pb.h"

int main() {
    Enterprise enterprise;
    enterprise.set_name("JSC Romashka");
    enterprise.set_foundation_year(2000);
    enterprise.set_legal_address("Moscow, st. Lenina, 1");
    enterprise.set_activity_type("Production");
    enterprise.set_has_foreign_activity(true);

    std::cout << "Name:\t" << enterprise.name() 
              << "\n" << "Year of foundation:\t" << enterprise.foundation_year()
              << "\n" << "Legal address:\t" << enterprise.legal_address()
              << "\n" << "Occupation:\t" << enterprise.activity_type() 
              << "\n" << "Foreign economic activity:\t" << std::boolalpha << enterprise.has_activity_type()
              << "\n";

}

